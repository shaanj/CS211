#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for(char **argvP = argv + 1; *argvP != argv[argc]; argvP++){
        for(char *CP = *argvP; *CP != '\0'; CP++){
            if(*CP == 'a' || *CP == 'e' || *CP == 'i' || *CP == 'o' || *CP == 'u' ||
            *CP == 'A' || *CP == 'E' || *CP == 'I' || *CP == 'O' || *CP == 'U'){
                printf("%c", *CP);    
            }
        }
    }
    printf("\n");
    return 0;
}
