#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MSIZE 1024

int main() {
	clock_t start, finish;
	double total_time;
	FILE *fp1 = NULL, *fp2 = NULL;
	char buf[MSIZE];
	start = clock();
	if ((fp1 = fopen("orig_file", "r")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	if ((fp2 = fopen("new_file2", "w")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	while (fread(buf, sizeof(buf), 1, fp1) > 0) {
		if (fwrite(buf, sizeof(buf), 1, fp2) < 0) {
			printf("write file failure!\n");
			exit(1);
		}
	}
	fclose(fp1);
	fclose(fp2);
	finish = clock();
	total_time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
	printf("Total time: %fms.\n", total_time);
	return 0;
}
	
