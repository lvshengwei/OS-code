#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define MSIZE 1024

int main() {
	clock_t start, finish;
	double total_time;
	int fd1, fd2;
	char buf[MSIZE];
	start = clock();
	if ((fd1 = open("orig_file", O_CREAT | O_RDONLY, 0644)) < 0) {
		printf("open file failure!\n");
		exit(1);
	}
	if ((fd2 = open("new_file1", O_CREAT | O_WRONLY, 0644)) < 0) {
		printf("create file failure!\n");
		exit(1);
	}
	while (read(fd1, buf, MSIZE) > 0) {
		if (write(fd2, buf, MSIZE) < 0) {
			printf("write file failure!\n");
			exit(1);
		}
	}
	close(fd1);
	close(fd2);
	finish = clock();
	total_time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
	printf("Total time: %fms.\n", total_time);
	return 0;
}
	
