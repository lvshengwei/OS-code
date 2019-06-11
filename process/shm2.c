#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define SHMKEY 20001
#define SIZE 512
#define SEMKEY1 20002
#define SEMKEY2 20003

extern int creatsem();
extern void P(), V();

void main(){
	char *segaddr;
	int segid, sid1, sid2, status;
	FILE *fp;
	if ((segid = shmget(SHMKEY, SIZE, IPC_CREAT|0666)) == -1){
		printf("shmget error.\n");
	}
	segaddr = shmat(segid, 0, 0);
	sid1 = creatsem(SEMKEY1);
	sid2 = creatsem(SEMKEY2);
	P(sid2);

	if (!fork()){
		P(sid2);
		fp = fopen("recv.txt", "w");
		fputs(segaddr, fp);
		fclose(fp);
		printf("Proc2 has received a message from proc1.\n");
		V(sid1);
	}
	else{
		P(sid1);
		fp = fopen("send.txt", "r");
		fgets(segaddr, 512, fp);
		fclose(fp);
		printf("Proc1 has sent a message to proc2.\n");
		V(sid2);
		wait(&status);
	}
}
		
