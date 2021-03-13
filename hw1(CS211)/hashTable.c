#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int SCount = 0;
int CCount = 0;

// create node struct
typedef struct Node {	
	int value;
	struct Node *next;
} Node;

void insert(Node **hashTable, int *key) {

	int index = *key % SIZE;
	if (index < 0){
		index *= -1;
	}
	
	Node * nptr = hashTable[index];
	while (nptr != NULL) {
		if (nptr->value == *key) {
            CCount++;
			return;
		}
		nptr = nptr->next;
	}
	
        Node *new = (Node*) malloc(sizeof(Node));
        new->value = *key;
        new->next = hashTable[index];
        hashTable[index] = new;
	
	return;

}

void search(Node **hashTable, int *key) {

	int index = *key % SIZE;
	if (index < 0) {
		index *= -1;
	}

	Node * nptr = hashTable[index];
	while (nptr != NULL){
		if (nptr->value == *key){
			SCount++;
			return;
		}
		nptr = nptr->next;		
	}
	return;
}

int main(int argc, char *argv[]){
	
	if (argc < 2) {
		return -1;
	}
	
	char *filename = argv[1];
	FILE *infile = fopen(filename,"r");

	char command[2];
	int value;

	Node ** hashT = (Node**) calloc(SIZE, sizeof(Node*));
	int i;
	for (i = 0; i < SIZE; i++) {
		hashT[i] = NULL;
	}

	while (fscanf(infile, "%s\t%d", command, &value) != EOF) {
		
		if (command[0] == 's'){
			search(hashT, &value);	
		}
		
		else {
			insert(hashT, &value);
		}	
	}
    printf("%d\n", CCount);
    printf("%d\n", SCount);
	
	for (i = 0; i < SIZE; i++){
		Node * nptr = hashT[i];
		while (nptr != NULL){
			Node * temp = nptr->next;
			free(nptr);
			nptr = temp;
		}
	}
	free(hashT);		
	fclose(infile);
	return 0;
}