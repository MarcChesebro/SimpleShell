#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

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

		if(strcmp(cmd, "quit")){
			free(cmdLine);
			free(filePath);
			exit(0);
		}else if(cmd != NULL) {
			char* token = strtok(NULL, " ");
			while(token != NULL){
			
				//add to vector

				token = strtok(NULL, " ");
			}
		}

//		childPid = fork();
//		if(childPid == 0){
//			//use execvp() to run command
//		}else{
//			wait(&status);
//			print status
//
	}
}
