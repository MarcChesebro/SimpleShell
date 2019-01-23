#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main (int argc, char **argv){

	while(1){
		int childPid;
		char* cmdLine;
		int status;
		char* filePath;

		cmdLine = malloc(250);
		filePath = malloc(250);

		//print path
		getcwd(filePath, 250);
		puts(filePath);

		fgets(cmdLine, 250, stdin);

		char* cmd;
		cmd = strtok(cmdLine, " ");
		printf("command: %s\n", cmd);

		char** arg_vector = (char**)malloc(sizeof(char*));
		memset(&arg_vector[0], 0, sizeof(arg_vector));

		if(strcmp(cmd, "Quit") == 0){
			printf("exiting...\n");
			free(cmdLine);
			free(filePath);
			exit(0);
		}else if(cmd != NULL) {
			printf("entered\n");
			int i = 0;
			char* token = strtok(NULL, " ");
			printf("yo\n");

			printf("OG token: %s\n", token);
			if(token) {
				while(token){
					printf("loop\n");

					//add to vector
					arg_vector[i] = token;
					printf("token: %s\n",token );
					printf("a_v: %s\n", arg_vector[i]);
					token = strtok(NULL, " ");
				}
			}else{
				printf("null token\n");
				arg_vector[0] = "";
			}
		}
		//printf("vector: %s\n", arg_vector);

		childPid = fork();
		if(childPid == 0){
			//use execvp() to run command
			execvp(cmd, arg_vector);
			printf("executed\n");
		}else{
			printf("parent\n");
			wait(&status);
			printf("Status: %d\n",status);

	}
}

return 0;
}
