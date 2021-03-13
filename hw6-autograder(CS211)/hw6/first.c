#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int misses;         //declaration of variables
int hits;
int reads = 0; 
int writes = 0;

unsigned long int counter;
struct Node** cache;
char *policy;

typedef struct Node{        //creating the struct "Node", with 3 variables associated with it.
    unsigned long long int tag;
    unsigned long int T;
    int alright;
}Node;

struct Node** CacheMoney(int S, int E){         //mallocing the space inside of the cache, and initializing the validity to 0 immediately
    cache = (Node**)malloc(sizeof(Node*) * S);

    for (int i = 0; i < S; i++){
        cache[i] = (Node*)malloc(sizeof(Node) * E);
    }

    for(int i = 0 ; i < S; i++){
        for(int j = 0; j < E; j++){
            cache[i][j].alright = 0;
        }
    }

    return cache;
}

void Magic(unsigned long long int TIndex, unsigned long long int EIndex, int E){        //this is where the magic happens
    int min = 0;
    for(int i = 0; i < E; i++){
        if(cache[EIndex][i].alright == 0){
            misses++;
	    counter++;
            reads++;
            cache[EIndex][i].alright = 1;
            cache[EIndex][i].tag = TIndex;
            cache[EIndex][i].T = counter;
            return;
        } else {
            if(strcmp(policy, "f") == 0 && cache[EIndex][i].tag == TIndex){
                hits++;
                return;
            }

            if(strcmp(policy, "l") == 0 && cache[EIndex][i].tag == TIndex){
                counter++;
                hits++;
                cache[EIndex][i].T = counter;
                return;
            }

            if(i == (E-1)){
		reads++;
                misses++;
                min = 0;

                for(int j = 0; j < E; j++){
                    if(cache[EIndex][j].T <= cache[EIndex][min].T){
                        min = j;
                    }
                }

                cache[EIndex][min].alright = 1;
                cache[EIndex][min].tag = TIndex;
                counter++;
                cache[EIndex][min].T = counter;
                return;
            }
        }
    }

    return;
}

int main(int argc, char* argv[]){       //main method that checks for error conditions, file opening, 
                                        //and calling other methods 
    if(argc != 6){
        return 0;
    }

    int CSize = atoi(argv[1]);
    if(ceil(log2(CSize)) != floor(log2(CSize))){
        return 0;
    }

    if(strcmp(argv[3], "fifo") !=0 && strcmp(argv[3],"lru") != 0){
        return 0;
    }

    if(strcmp(argv[3], "lru") == 0){
        policy = "l";
    }

    if(strcmp(argv[3], "fifo") == 0){
        policy = "f";
    }
    
    int BSize = atoi(argv[4]);
    if(ceil(log2(BSize)) != floor(log2(BSize))){
        return 0;
    }

    char assoTest[6] = "assoc:";
    int E = 0;
    int S = 0;
    
    if(strcmp(argv[2], "direct") == 0){
            E = 1;
            S = CSize/BSize;
    }
    else if(strcmp(argv[2], "assoc") == 0){
            E = CSize/BSize;
            S = 1;
    } else {
        for(int i = 0; i < 6; i++){
            if(assoTest[i] != argv[2][i]){
                return (-1);
            }
        }

        sscanf(argv[2], "assoc:%d", &E);
        if(ceil(log2(E)) != floor(log2(E))){
                return 0;
            } else {
                S = CSize/BSize/E;
            } 
    }
 
    FILE* fp = fopen(argv[5],"r");

    if(fp == NULL){
        return 0;
    }

    int Ebit = log2(S);
    int Bbit = log2(BSize);
    
    cache = CacheMoney(S, E);
    unsigned long long int Emas = ((1 << Ebit) - 1);
    unsigned long long int TIndex;
    unsigned long long int EIndex;
 
    char WorR;
    unsigned long long int Ad = 0;

    while(fscanf(fp, "%*s %c %llx", &WorR, &Ad) != EOF){
        EIndex = (Ad >> Bbit)&Emas;
        TIndex = Ad >> (Bbit + Ebit);
            if(WorR == 'W'){
                writes++;
                Magic(TIndex, EIndex, E);
            }
            else if(WorR == 'R'){
                Magic(TIndex, EIndex, E);
            }
    }

    printf("Memory reads: %d\n", reads);        //print statements for reads, writes, hits, and misses
    printf("Memory writes: %d\n", writes);
    printf("Cache hits: %d\n", hits);
    printf("Cache misses: %d\n", misses);
    
    BeFree(cache, S, E);
    fclose(fp);

    return 0;
}

void BeFree(Node** cache, int S, int E){        //method to free memory allocations
    for(int i = 0; i < S; i++){
        free(cache[i]);
    }

    free(cache);
    return;
}
