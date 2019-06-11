#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char buf[64];
	int fd, n;
	FILE *fp = NULL;
	fd = open("fifo", O_RDONLY|O_NDELAY);
	if ((fp = fopen("text7.txt", "w")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		fputs(buf, fp);
	}
	close(fd);
	fclose(fp);
	return 0;
}
	
