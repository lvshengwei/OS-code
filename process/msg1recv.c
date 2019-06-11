#include "msg1.h"

int main(){
	struct msgtype buf;
	int qid;
	FILE *fp;
	if ((qid = msgget(MSGKEY, IPC_CREAT|0666)) == -1){
		return -1;
	}
	msgrcv(qid, &buf, 512, 1, MSG_NOERROR);
	printf("Process2 has received a message from process1.\n");
	fp = fopen("recv.txt", "w");
	fputs(buf.text, fp);
	fclose(fp);
	return 0;
}
