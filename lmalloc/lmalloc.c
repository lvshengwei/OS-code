#include <stdio.h>
#include <stdlib.h>

#define TOTAL_SIZE 1000

// define struct of free memory area
typedef struct map{
	unsigned size;
	char *addr;
	struct map *next, *prev;
}map;

map *cur, *coremap;//current pointer & header pointer

//response to invalid input
void wrongInput(){
	printf("\nUsage:\n");
	printf("\tm\tallocate memory\n");
	printf("\tf\tfree memory\n");
	printf("\tp\tprint all free memory\n");
	printf("\tq\tquit program\n\n");
}

//memory allocation
char* lmalloc(unsigned size){
	register char *a;
	register map *bp = cur;
	do{
		//find a suitable free area
		if (bp->size >= size){
			//change memory entry
			a = bp->addr;
			bp->addr += size;
			bp->size -= size;
			cur = bp->next;
			//delete redundant entry
			if (bp->size == 0 && bp != bp->next){
				if (bp == coremap){
					coremap = bp->next;
				}
				bp->prev->next = bp->next;
				bp->next->prev = bp->prev;
				free(bp);
			}
			return a;
		}
		bp = bp->next;
	}while (bp != cur);
	//no suitable free area
	return NULL;
}

//free memory
void lfree(char* addr, unsigned size){
	register map *bp, *t;

	//no free memory now
	if (coremap->size == 0){
		coremap->addr = addr;
		coremap->size = size;
	}
	else{
		//locate
		for (bp = coremap; bp->addr < addr && bp->next != coremap; bp = bp->next);
		if (bp->addr < addr){
			bp = bp->next;
		}
		//merge with previous area
		if (bp->prev->addr + bp->prev->size == addr){
			bp->prev->size += size;
			//merge with next area
			if (addr + size == bp->addr){
				bp->prev->size += bp->size;
				bp->prev->next = bp->next;
				bp->next->prev = bp->prev;
				free(bp);
			}
		}
		else{
			//merge with next area
			if (addr + size == bp->addr){
				bp->addr -= size;
				bp->size += size;
			}
			//create a new struct to store this area
			else{
				t = (map *)malloc(sizeof(map));
				t->addr = addr;
				t->size = size;
				t->prev = bp->prev;
				t->next = bp;
				bp->prev->next = t;
				bp->prev = t;
				//change coremap
				if (addr < coremap->addr){
					coremap = t;
				}
			}
		}
	}
}

//print memory mapping table
void printMemoryMapping(){
	register map *bp = coremap;
	printf("\nMemory mapping table:\n");
	printf("\tAddr          \t\tSize\n");
	//scan the whole chain
	do{
		printf("\t%p\t\t%u\n", bp->addr, bp->size);
		bp = bp->next;
	}while (bp != coremap);
	printf("\n");
}

int main(){
	printf("Malloc Simulation\n");
	printf("Initializing...\n\n");

	//initialize memory pool and first block
	char *mempool = (char *)malloc(TOTAL_SIZE);
	coremap = (map *)malloc(sizeof(map));
	coremap->size = TOTAL_SIZE;
	coremap->addr = mempool;
	coremap->next = coremap;
	coremap->prev = coremap;
	cur = coremap;

	while (1){
		printf(">>> ");
		char c, getBuff;
		unsigned size;
		int rec;
		char *addr;
		
		//discard blank character
		do{
			c = getchar();
		}while (c == '\n' || c == '\t' || c == ' ');
		//quit
		if (c == 'q'){
			break;
		}
		//allocate memory
		else if (c == 'm'){
			rec = scanf("%u", &size);
			if (rec == 1 && size > 0){
				addr = lmalloc(size);
				if (addr){
					printf("\nAllocate memory: %p (%u)\n\n", addr, size);
				}
				else{
					printf("\nNot enough memory\n\n");
				}
			}
			else if (size == 0){
				printf("\nSize must be positive\n\n");
			}
			else{
				wrongInput();
			}
		}
		//free memory
		else if (c == 'f'){
			rec = scanf("%p%u", &addr, &size);
			if (rec == 2 && size > 0){
				lfree(addr, size);
				printf("\nFree memory: %p (%u)\n\n", addr, size);
			}
			else if (size == 0){
				printf("\nSize must be positive\n\n");
			}
			else{
				wrongInput();
			}
		}
		//print memory mapping table
		else if (c == 'p'){
			printMemoryMapping();
		}
		//wrong input
		else{
			wrongInput();
		}

		//flush input buffer
		do{
			getBuff = getchar();
		}while (getBuff != '\n');
	}
	//clear
	free(mempool);
	free(coremap);

	return 0;
}
