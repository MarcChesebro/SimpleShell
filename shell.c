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
 
		cmdLine[strcspn(cmdLine,"\n")] = 0;
		char* cmd;
		cmd = strtok(cmdLine, " ");
		printf("command: %s\n", cmd);

		char** arg_vector = (char**)malloc(sizeof(char*) * 5);
		memset(&arg_vector[0], 0, sizeof(arg_vector));
		//char arg_vector[10][90];
		

		if(strcmp(cmd, "quit") == 0){
			printf("exiting...\n");
			wait(&status);
			free(cmdLine);
			free(filePath);
			exit(0);
		}else if(cmd != NULL) {
			//printf("entered\n");
			int i = 1;
			char* token = strtok(NULL, " ");
			//printf("yo\n");

			printf("OG token: %s\n", token);
			arg_vector[0] = (char*)malloc(sizeof(token));
			arg_vector[0] = cmd;
			printf("cmd: %s\n",arg_vector[0]);
			if(token) {
				while(token){
					printf("loop\n");

					//add to vector
					arg_vector[i] = (char*)malloc(sizeof(token));
					arg_vector[i] = token;
					printf("token: %s\n",token );
					printf("a_v: %s\n", arg_vector[i]);
					token = strtok(NULL, " ");
				}
				i = i+1;
				
				printf("Val of i: %d\n",i);
			}else{
				printf("null token\n");
				//arg_vector[0] = "";
			
			}

			printf("Val of i: %d\n",i);
			arg_vector[i] = NULL;

		        int u = 0;
			while(u<i+1) {
			   printf("argvector pos: %d, val: %s\n",u,arg_vector[u]);
			   u++;
			}
		}
                
		// add terminating char
		//arg_vector[i+1] = NULL;
		printf("vector: %s\n", &arg_vector);

		int p[2];
		pipe(p);
		childPid = fork();
	
		if(childPid == 0){
			//use execvp() to run command
			dup2(p[1], 1);	
			close(p[0]);
			
			execvp(arg_vector[0], arg_vector); 
			close(p[1]);
			printf("executed\n");
			break;
		}else{
			close(p[1]);
			printf("parent\n");
		      	FILE *stream;
			int c;
			stream = fdopen (p[0], "r");
			while ((c = fgetc (stream)) != EOF)
				putchar (c);
			fclose (stream);
			
			close(p[0]);
			
			wait(&status);
			printf("Status: %d\n",status);

	}
}

return 0;
}
