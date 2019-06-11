#include "msg1.h"

int main(){
	struct msgtype buf;
	int qid;
	FILE *fp;
	fp = fopen("send.txt", "r");
	char str[512];
	fgets(str, 512, fp);
	qid = msgget(MSGKEY, IPC_CREAT|0666);
	buf.mtype = 1;
	strcpy(buf.text, str);
	msgsnd(qid, &buf, sizeof(buf.text), 0);
	printf("Process1 has sent a message to process2.\n");
	fclose(fp);
	return 0;
}
