#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char buf[64];
	int fd;
	FILE *fp = NULL;
	mknod("fifo", S_IFIFO|0666, 0);
	fd = open("fifo", O_WRONLY);
	if ((fp = fopen("text.txt", "r")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	while (fgets(buf, sizeof(buf), fp)) {
		write(fd, buf, sizeof(buf));
	}
	close(fd);
	fclose(fp);
	return 0;
}
	
