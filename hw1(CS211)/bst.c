#include <stdio.h>
#include <stdlib.h>

typedef struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
};

struct treenode *root = NULL;

struct treenode* insertion(struct treenode *root, int value, int h){
    if(root == NULL){
        struct treenode *tnode = malloc(sizeof(struct treenode));
        tnode->data = value;
        tnode->left = NULL;
        tnode->right = NULL;
        return tnode;
    }

    if(root->data == value){

    } else if(value > root->data){
        root->right = insertion(root->right, value, h+1);
    } else if(value < root->data){
        root->left = insertion(root->left, value, h+1);
    }
    return root;
}

void freeBST(struct treenode* root){
    if(root == NULL){
        return;
    } else {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
        root = NULL;
    }
}

void InOrder(struct treenode* root){
    if(root == NULL){
        return;
    }
    InOrder(root->left);
    printf("%d\t", root->data);
    InOrder(root->right);
}

int main(int argc, char* argv[])
{
    FILE *fileP = fopen(argv[1], "r");
    if(fileP == NULL){
        printf("error");
        exit(0);
    }

    char eye;
    int value;
    int h = 1;

    while(fscanf(fileP, "%c\t%d\n", &eye, &value) == 2){
        if(eye == 'i'){
            root = insertion(root, value, h);
        }
    }
    fclose(fileP);
    InOrder(root);
    printf("\n");
    freeBST(root);
    return 0;
}