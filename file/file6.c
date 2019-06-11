#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char buf[64];
	FILE *fp = NULL;
	int chan[2];
	pipe(chan);
	if (fork()) {
		close(chan[0]);	
		if ((fp = fopen("text.txt", "r")) == NULL) {
			printf("open file failure!\n");
			exit(1);
		}
		while (fgets(buf, sizeof(buf), fp)) {
			write(chan[1], buf, sizeof(buf));
		}
		close(chan[1]);
	}
	else {
		close(chan[1]);
		if ((fp = fopen("text6.txt", "w")) == NULL) {
			printf("open file failure!\n");
			exit(1);
		}
		while (read(chan[0], buf, sizeof(buf)) > 0) {
			fputs(buf, fp);
		}
		close(chan[0]);
	}
	fclose(fp);
	return 0;
}

