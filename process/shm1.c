#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void semcall(int sid, int op){
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = op;
	sb.sem_flg = 0;
	if (semop(sid, &sb, 1) == -1){
		printf("semop error.\n");
	}
}

int creatsem(key_t key){
	int sid;
	union semun{
		int val;
		struct semid_ds *buf;
		ushort *array;
	} arg;
	if ((sid = semget(key, 1, IPC_CREAT|0666)) == -1){
		printf("semget error.\n");
	}
	arg.val = 1;
	if (semctl(sid, 0, SETVAL, arg) == -1){
		printf("semctl error.\n");
	}
	return sid;
}

void P(int sid){
	semcall(sid, -1);
}

void V(int sid){
	semcall(sid, 1);
}



