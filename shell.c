#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <sys/resource.h>

int main (int argc, char **argv){

	long invcsw_total = 0;
	while(1){
		int childPid;
		char* cmdLine;
		int status;
		char* filePath;

		cmdLine = malloc(250);
		filePath = malloc(500);

		getcwd(filePath, 500);
		puts(filePath);

		fgets(cmdLine, 250, stdin);

		cmdLine[strcspn(cmdLine,"\n")] = 0;
		char* cmd;
		cmd = strtok(cmdLine, " ");

		char** arg_vector = (char**)malloc(sizeof(char*) * 5);
		memset(&arg_vector[0], 0, sizeof(arg_vector));

		if(strcmp(cmd, "quit") == 0){
			printf("exiting...\n");
			wait(&status);
			free(cmdLine);
			free(filePath);
			exit(0);
			// cd isn't a part of execvp
		} else if(strcmp(cmd,"cd") == 0) {
		  	char* path = strtok(NULL," ");
				if (path) {
					chdir(path);
					getcwd(filePath, 500);
					puts(filePath);
				} else {
				  	chdir(getenv("HOME"));
				    getcwd(filePath, 250);
				    puts(filePath);
				}
		}
		else if(cmd != NULL) {
			int i = 1;
			char* token = strtok(NULL, " ");
			arg_vector[0] = (char*)malloc(sizeof(token));
			arg_vector[0] = cmd;
			if(token) {
				while(token){
					arg_vector[i] = (char*)malloc(sizeof(token));
					arg_vector[i] = token;
					token = strtok(NULL, " ");
				}
				i = i+1;

			}
			arg_vector[i] = NULL;
		}
		clock_t start, end;
		start = clock();
		childPid = fork();

		if(childPid == 0){
			execvp(arg_vector[0], arg_vector);
			break;
		}else{
			struct rusage usage;
      int ret;
			wait(&status);

      ret = getrusage(RUSAGE_CHILDREN, &usage);
			end = clock();

			double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

			printf("CPU time: %f\n", cpu_time);
			printf("involentary context switches: %ld\n", usage.ru_nivcsw - invcsw_total);
			invcsw_total = usage.ru_nivcsw;
		}
}

return 0;
}
