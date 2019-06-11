#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char c;
	FILE *fp1 = NULL, *fp2 = NULL;
	if ((fp1 = fopen("text.txt", "r")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	if ((fp2 = fopen("text4.txt", "w")) == NULL) {
		printf("open file failure!\n");
		exit(1);
	}
	while ((c = fgetc(fp1)) > 0) {
		if (fputc(c, fp2) < 0) {
			printf("write file failure!\n");
			exit(1);
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
	
