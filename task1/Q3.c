#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
int main(int argc,char **argv) {

	time_t t;   // not a primitive datatype
	time(&t);	
    	pid_t pid,ppid, child_A,child_B;
	child_A= fork();

	if (child_A < 0) {
		perror("fork() failure\n");
		return 1;
	}

	   // Child process A
	   if (child_A == 0) {
			printf("This is child process A\n");
			//pid = (long)getpid();
			//ppid = (long)getppid();
			printf("Current local time and date: %s", ctime(&t));
			printf("Process id is %ld and PPID is %ld\n", (long)getpid(), (long)getppid());
	   } else { 
	   // Child process B
			sleep(4);
			child_B=fork();
			if(child_B==0){
				printf("This is parent process B\n");
				printf("Process id is %ld and PPID is %ld\n", (long)getpid(), (long)getppid());
				system("traceroute 8.8.8.8");
 				printf("Work completed!");
			}
			//parent process
			else{
			    	printf("Parent Process ID is : %ld\n", (long)getpid());
			}	
	}
	   return 0;
}
