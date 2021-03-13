#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node{
    int data;
    struct Node* next;
};

struct Node *head = NULL;
int NCounter = 0;

void printList(struct Node* Head) { 

    if (Head == NULL) {
        return;
    }

    while (Head != NULL) {
        if (Head->data == INT_MAX) {
            Head = Head->next;
            continue;
        }

        printf("%d\t", Head->data);
        Head = Head->next;
    }

    printf("\n");
}

void freeList(struct Node* Head)
{
    struct Node* nptr = Head;
    while(nptr != NULL){
        struct Node* temp = nptr;
        nptr = nptr->next;
        free(temp);
    }
}

void insertion(int i){
    struct Node* pre = NULL;
    struct Node* temp = malloc(sizeof(struct Node));
    temp->data = i;
    temp->next = NULL;

    if(head == NULL){
        head = temp;
        NCounter++;
        return;
    }

    struct Node* nptr = head;
    while(nptr != NULL){
        if(i == nptr->data && pre == NULL){
            temp->next = nptr;
            head = temp;
            NCounter++;
            return;
        } else if (i == nptr->data && pre != NULL){
            temp->next = nptr;
            pre->next = temp;
            NCounter++;
            return;
        } else if(i > nptr->data && nptr->next == NULL){
            nptr->next = temp;
            nptr = temp;
            NCounter++;
            return;
        } else if(i < nptr->data && pre != NULL){
            temp->next = nptr;
            pre->next = temp;
            NCounter++;
            return;
        } else if(i < nptr->data && pre == NULL){
            temp->next = nptr;
            head = temp;
            NCounter++;
            return;
        }
        pre = nptr;
        nptr = nptr->next;
    }

}

void deletion(int d){
    struct Node* pre = NULL;
    struct Node* nptr = head;

    if(nptr == NULL){
        return;
    }

    if(nptr->data == d){
        head = nptr->next;
        free(nptr);
        NCounter--;
        return;
    }
    
    while(nptr != NULL && nptr->data != d){
        pre = nptr;
        nptr = nptr->next;
    }
    
    if(nptr == NULL){
        return;
    } else {
        pre->next = nptr->next;
        free(nptr);
        NCounter--;
        return;
    }
}

int main (int argc, char* argv[]){
    char *filename = argv[1];
    FILE *infile = fopen(filename, "r");

    int value;
    char iOrd;
    while(fscanf(infile, "%c\t%d\n", &iOrd, &value) == 2){
        if(iOrd == 'i'){
            insertion(value);
        } else if(iOrd == 'd') {
            deletion(value);
        }
    }
    
    printf("%d\n", NCounter);
    printList(head);
    freeList(head);
    return 0;
}