#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

	int fd[2]; // f[0] read ; f[1] write
	pipe(fd);

	pid_t pid = getpid();

	printf("I'm SHELL process, with PID: %d - Main command is man grep | grep -A 4 -e \"  -e P\" > output.txt\n", pid);

	int rc = fork();

	if (rc<0){
		fprintf(stderr, "forkfailed\n");
		exit(1);
	}
	else if (rc==0){ 
		/// man

		pid_t pid = getpid();
		printf("I'm MAN process, with PID: %d - My command is: man grep\n", pid);

		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);

		char* myargs[3];
		myargs[0] = strdup("man");
		myargs[1] = strdup("grep");
		myargs[2] = NULL;
		execvp(myargs[0],myargs);
	}
	else{ 
		
		wait(NULL);

		int rc2=fork();

		if (rc2<0){
			fprintf(stderr, "forkfailed\n");
			exit(1);			
		}
		else if (rc2==0){

			pid_t pid = getpid();
			printf("I'm GREP process, with PID: %d - My command is: grep -A 4 -e \"  -e P\" > output.txt\n", pid);

			close(fd[1]);
		/// from pipe to grep

			int fd2 = open("output.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
			dup2(fd2,STDOUT_FILENO);
			dup2(fd2,2);

			close(fd2);
			
			dup2(fd[0], STDIN_FILENO);
			char* myargs[6];
			myargs[0] = strdup("grep");
			myargs[1] = strdup("-A");
			myargs[2] = strdup("4");
			myargs[3] = strdup("-e");
			myargs[4] = strdup("  -e P");
			myargs[5] = NULL;
			execvp(myargs[0],myargs);
		}
		else{
			pid_t pid = getpid();
			close(fd[1]);
			close(fd[0]);
			wait(NULL);
			printf("I'm SHELL process with PID: %d - execution completed, you can find the results in output.txt\n", pid);
		}
	}
	return 0;
}
