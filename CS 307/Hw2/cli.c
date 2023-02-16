// TODO

// read command     +
// parse line       +
// write parse.txt  + 

// create fork to run new process 						+
//  - redirect to txt 									+
//  - if command == wait : not new process -> wait 		+
 
// background jobs										+

// solve concurrency -> cannot mutex to processes		+

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <pthread.h>
#include <sys/wait.h>

pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

#define MAX_LINE_LENGTH 100

typedef struct {
    struct proc_node** head;
    struct proc_node* node;
} myarg_t;

struct proc_node{
	int pid;
	struct proc_node* next;
	int fd[2];
	char* myargs[6];
};

struct thread_node{
	pthread_t id ;
	struct thread_node* next;
};

char** parse(char ** myargs, char* line){


	char* token;
	char s[2]=" ";
	char n[2]="\n";

	char* lineCopy = strdup(line);


	for(int i =0 ; i<6;i++){
		myargs[i]="";
	}

	token = strchr(line,'&');
	if(token!=NULL)
		myargs[5] = "y";
	else
		myargs[5] = "n";

	// getting command
	token =strtok(lineCopy, s);

	myargs[0] = strdup(token);

	// getting second argument
	if(token[0]=='w' &&  token[1]=='a' &&  token[2]=='i'&&  token[3]=='t')
		;
	else{
		token = strtok(NULL, s);

		// if jumps to
		if( (token[0] <= 'z' && token[0] >= 'a') || (token[0] <= 'Z' && token[0] >= 'A'))  
			myargs[1] = strdup(token);
		else
			myargs[1] = "";
	

		token = strchr(line,'-');
		if(token!=NULL)
			myargs[2] = strndup(token, 2);
		else
			myargs[2] = "";

		token = strchr(line,'<');
		if(token!=NULL){
			myargs[3] = strndup(token,1);
			strtok(token,s);
			myargs[4] = strdup(strtok(NULL,s));
		}
		else{
			token = strchr(line,'>');
			if(token!=NULL){
				myargs[3] = strndup(token,1);
				strtok(token,s);
				myargs[4] = strdup(strtok(NULL,s));
			}
			else{
				myargs[3] = "-";
				myargs[4] = "-";
			}

		}
	}
	
	for(int i =0 ; i<5;i++){
		char *newline = strchr(myargs[i],'\n');
		if(newline !=NULL)
			*newline ='\0';
	}

	return myargs;
}

void printParse(char** args){

	FILE *f = fopen("parse.txt","a");
	if(f==NULL){
		printf("Error opening file\n");
		exit(1);
	}
	fprintf(f, "----------\n");
	fprintf(f, "Command: %s\n",args[0] );
	fprintf(f, "Inputs: %s\n", args[1]);
	fprintf(f, "Options: %s\n", args[2]);
	fprintf(f, "Redirection: %s\n",args[3]=="-" ? "-" : args[3]);
//	fprintf(f, "Redirection Check: %s\n",args[4]);
	fprintf(f, "Background Job: %s\n",args[5]);
	fprintf(f, "----------\n");
	fclose(f);
}


void add_node(struct proc_node** head, int pid, char**myargs){
	//lock

	struct proc_node* new_node =malloc(sizeof(struct proc_node));
	new_node->pid = pid;
	new_node->next = *head;
	new_node->myargs[0]=strdup(myargs[0]);
	new_node->myargs[1]=strdup(myargs[1]);
	new_node->myargs[2]=strdup(myargs[2]);
	new_node->myargs[3]=strdup(myargs[3]);
	new_node->myargs[4]=strdup(myargs[4]);
	new_node->myargs[5]=strdup(myargs[5]);
	*head=new_node;
	//unlock
}

void delete_node(struct proc_node** head, int pid){
	//lock

	struct proc_node* tmp=*head;
	if(head==NULL)
		return ;

	if ((*head)->pid == pid){
		tmp = *head;
		*head= tmp->next;
		free(tmp);
	}
	else{
		while(tmp->next != NULL && tmp->next->pid != pid){
			tmp= tmp->next;
		}
		if(tmp->next->pid == pid){
			struct proc_node* tmp2 = tmp->next;
			tmp->next = tmp2->next;
			free(tmp2);
		}
		else
			return ;
	}
	//unlock
}

void add_node_t(struct thread_node** head, long unsigned int pid){
	struct thread_node* new_node =malloc(sizeof(struct thread_node));
	new_node->id = pid;
	new_node->next = *head;
	*head=new_node;
}

void delete_node_t(struct thread_node** head, long unsigned int pid){
	//lock

	struct thread_node* tmp=*head;
	if(head==NULL)
		return ;

	if ((*head)->id == pid){
		tmp = *head;
		*head= tmp->next;
		free(tmp);
	}
	else{
		while(tmp->next != NULL && tmp->next->id != pid){
			tmp= tmp->next;
		}
		if(tmp->next->id == pid){
			struct thread_node* tmp2 = tmp->next;
			tmp->next = tmp2->next;
			free(tmp2);
		}
		else
			return ;
	}
	//unlock
}


void *displayThread(void *arg)
{
	pthread_mutex_lock(&output_mutex);

	pthread_t tid = pthread_self();

    int fd = *(int *)arg;

    // Read from the pipe and print the output
    char line[50000];
    read(fd, line, sizeof(line));
    printf("---- %lu\n",tid);
    printf("%s", line);
    printf("---- %lu\n",tid);

    pthread_mutex_unlock(&output_mutex);

    return NULL;
}


int main(int argc, int* argv[]){


	//clearing parse.txt
	FILE *f = fopen("parse.txt","w");
	fclose(f);

	FILE *textfile = fopen("commands.txt", "r");

	if(textfile == NULL)
		return 1;


	/// a lot of variable

	int status;

	char line[MAX_LINE_LENGTH];

	int rc=-1;
	char* myargs[6];
	char* data;

	//end of variables

	struct proc_node* head = malloc(sizeof(struct proc_node)); // dummy node
	head->pid =0;
	head->next = NULL;

	struct thread_node* head_thread = malloc(sizeof(struct proc_node));
	head_thread->id =0;
	head_thread->next = NULL; 

	struct proc_node* tmp = head;

	while(fgets(line, MAX_LINE_LENGTH, textfile) && rc!=0){

		parse(myargs, line);
		printParse(myargs);

		if(line[0]=='w'&&line[1]=='a'&&line[2]=='i'&&line[3]=='t') /// wait all processes : hopefully
		{
			while(head->pid!=0){ ////// all processes
				// check if the process is running
				pthread_t p;

				waitpid(head->pid,&status,0);
				pthread_create(&p, NULL, displayThread, &(head->fd[0]));
				pthread_join(p,NULL);


				delete_node(&head,head->pid);
			}
		}
		else{	
			add_node(&head,rc, myargs);
			pipe(head->fd);
			
			rc = fork();
			if (rc==-1){
				printf("fork failed\n");
			}
			else if (rc>0){
				//// Parent
				head->pid =rc;

				if(strcmp(myargs[5],"y")!=0) {// if not background jo
					waitpid(rc, &status, 0);
					pthread_t p;
					if (strcmp(myargs[3],">")!=0){ /// this shouldnt change anything

						pthread_create(&p, NULL, displayThread, &(head->fd[0]));
						pthread_join(p,NULL);
					}
					close((head->fd)[1]);
					close((head->fd)[0]);
					delete_node(&head,rc);
				}
				struct proc_node* temp = head;
				struct proc_node* temp2 = temp;

				while(temp->pid != 0){ ////// all processes
					// check all processes is they running running

					if(kill(temp->pid,0) == 0){		
						///if process is running
						temp=temp->next;				
					}
					else{
						pthread_t p;
						//process is not running

						if (strcmp(temp->myargs[3],">")!=0){

							add_node_t(&head_thread, p);
							pthread_create(&p, NULL, displayThread, &(temp->fd[0]));
						}

						temp2=temp;
						temp=temp->next;
						delete_node(&head,temp2->pid);
					}
				}
			}
			else{ /// if child

				if(strcmp(myargs[3], "<")==0){/// if input redirection
					close(STDIN_FILENO);
					open(myargs[4], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
					close((head->fd)[0]);
					dup2((head->fd)[1],STDOUT_FILENO);
				}
				else if(strcmp(myargs[3], ">")==0){/// if output redirection
					close(STDOUT_FILENO);
					open(myargs[4], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
				}
				else{
					close((head->fd)[0]);
					dup2((head->fd)[1],STDOUT_FILENO);
				}
				
				char* execvp_args[4];
				int arg_num =0;


				for(int i =0;i<3;i++){
					if(strcmp(myargs[i],"")!=0){
						execvp_args[arg_num]=strdup(myargs[i]);
						arg_num++;
					}
				}
				execvp_args[arg_num]=NULL;
				
				execvp(execvp_args[0],execvp_args);
			}
		}
	}
	/// wait all

	while(head->pid!=0){ ////// all processes
		// check if the process is running
		pthread_t p;

		waitpid(head->pid,&status,0);
		pthread_create(&p, NULL, displayThread, &(head->fd[0]));
		add_node_t(&head_thread, p);


		close((head->fd)[1]);
		delete_node(&head,head->pid);
	}

	while (head_thread->id !=0){
		pthread_join(head_thread->id,NULL);
		delete_node_t(&head_thread, head_thread->id);
	}
	fclose(textfile);
	
	return 0;
}