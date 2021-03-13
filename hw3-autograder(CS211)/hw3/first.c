#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short set(unsigned short *p, int num, int var){
    if(var == 0){
        *p &= ~(1 << num);
    }
    else if(var == 1){
        *p |= 1 << num;
    }
    return *p;
}

unsigned short comp(unsigned short *p, int var){
    *p ^= 1 << var;
    return *p;
}

void get(unsigned short *p, int num){
    int bit = (*p & (1 << num)) >> num;
    printf("%d\n", bit);
}

int main(int argc, char* argv[])
{
    FILE *fname;                            //file pointer
    fname = fopen(argv[1], "r");            //opening file and reading argv[1] value

    if(fname == NULL){                      //check to see if the file is null
        return 0;
    }

    unsigned short *x = (unsigned short *)malloc(sizeof(unsigned short));   //memory allocation for the short pointer x
    fscanf(fname, "%hu", x);                                                //putting that value in the file into x
    char cmd[10];
    int a, b;

    while(fscanf(fname, "%s\t%d\t%d", cmd, &a, &b) != EOF){                 //while loop to check if its not the end of the file
        if(strcmp(cmd, "set") == 0){                                        //if set, sent the ath bit of x to the value b
            *x = set(x, a, b);
            printf("%hu\n", *x);
        }
        else if(strcmp(cmd, "comp") == 0){                                  //if comp, switch the ath bit of x to 1 if the bit has 0, and 0 if otherwise
            *x = comp(x, a);
            printf("%hu\n", *x);
        }
        else if(strcmp(cmd, "get") == 0){                                   //if get, just return the ath bit of x
            get(x, a);
        }
    }
    fclose(fname);                                                          //close the file
    free(x);                                                                //free the memory taken up by x
}
