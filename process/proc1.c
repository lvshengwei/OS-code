#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int pid, status = 1;
	void func();
	signal(SIGUSR1, func);
	while ((pid = fork()) == -1);
	if (pid){
		printf("It is parent process.\n");
		printf("Parent: will send signal.\n");
		sleep(1);
		kill(pid, SIGUSR1);
		wait(&status);
		printf("status=%d: Parent finished.\n", status);
	}
	else{
		printf("It is child process.\n");
		sleep(10);
		printf("Child: signal is received.\n");
		execl("/bin/ls", "ls", "-l", (char*)0);
		printf("execl error.\n");
		exit(2);
	}
	printf("Parent process finished.\n");
	return 0;
}

void func(){
	printf("It is signal processing function.\n");
}

