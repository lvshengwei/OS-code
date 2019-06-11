#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char buf[64];
	FILE *fp1 = NULL, *fp2 = NULL;
	if ((fp1 = fopen("text.txt", "r")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	if ((fp2 = fopen("text5.txt", "w")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	while (fgets(buf, sizeof(buf), fp1)) {
		if (fputs(buf, fp2) < 0) {
			printf("write file failure!\n");
			exit(1);
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
	
