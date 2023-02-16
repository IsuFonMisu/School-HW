#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>


struct user{
	char g;
	char name[20];
	char surname[20];
	struct user* next;
};

void add_node( struct user** head,char g, char name[], char surname[]){
	struct user* temp = malloc(sizeof(struct user));
	strncpy(temp->name, name,20 );
	strncpy(temp->surname, surname,20);
	temp->g = g;
	temp->next = *head;
	*head = temp;
}

void clear_list(struct user** head){
	struct user* temp = *head;
	for(; temp; *head=temp){
		temp = (*head)->next;
		free(*head);
	}
}

void read_database(struct user** head){
	FILE *fptr;
	fptr = fopen("database.txt","r");

	char c[2];
	char name[20];
	char surname[20];
	while (fscanf(fptr, "%s %s %s", c,name,surname)==3){
		add_node(head, c[0], name, surname);
	}
}


struct user* search_user(char name[], struct user* head){
	for(; head->next; head= head->next){
		if (strcmp(name, head->name)==0){
			return head;
		}
	}
	return NULL;
}

void fix_file(char path[], char filename[], struct user* head){
	FILE *fptr;

	char fname[200]="";
	strcat(fname, path);
	strcat(fname, filename);


	if (!strcmp(fname, "./database.txt"))
		return;

	fptr = fopen(fname,"r+");

	char token[30];
	char name[20];
	char surname[20];
	char c;
	struct user* temp = NULL;
	while(fscanf(fptr, "%s", token)==1){

		temp  = search_user(token, head);

		if(temp){

			fseek(fptr,-strlen(token)-4, SEEK_CUR);

			if(temp->g =='f') /// without checking if  incorrect directly write correct
				fputs("Ms.",fptr);
			else
				fputs("Mr." ,fptr);

			fseek(fptr,  strlen(token)+4, SEEK_CUR);

			fscanf(fptr,  "%s", surname);

			if(strcmp(surname, temp->surname)){ /// if not same
				fseek(fptr, -strlen(surname)-2, SEEK_CUR);
				fputs(temp->surname, fptr);
				fseek(fptr, strlen(surname)+2, SEEK_CUR);
			}
		}
	}
}



void fix_directory(char path[], char dirname[], struct user* head){

	DIR *d;
	struct dirent * dir;

	char dirpath[200]="";
	strcat(dirpath, path);
	strcat(dirpath, dirname);
	strcat(dirpath, "/");

	d = opendir(dirpath);

	if(d){
		while((dir = readdir(d)) !=NULL){
			long unsigned l = strlen(dir->d_name);
			if((dir->d_name[0])!='.' && dir->d_type == DT_DIR){ /// if it is a directory 
				fix_directory(dirpath, dir->d_name, head); /// instead of print fix
			}
			else if((dir->d_name)[l-4]=='.' && (dir->d_name)[l-3] =='t' && (dir->d_name)[l-2]=='x' && (dir->d_name)[l-1]=='t'){
				fix_file(dirpath, dir->d_name,head); /// fix given file
			}
		}
		closedir(d);
	}
}

int main(int argc, char *argv[]) {

	struct user* head=NULL;

	add_node(&head,'\0',"","");
	read_database(&head);

	char *path = "";
	char *root = ".";

	fix_directory(path, root, head);
	clear_list(&head);
	return 0;
}
