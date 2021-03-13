#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *ptr = fopen(argv[1], "r");
    if(ptr == NULL){
        return 0;
    }
    
    char* lines[100];                   //char* array for storing lines in file
    for(int i = 0; i < 100; i++){       //line 14-15 mallocing
        lines[i] = (char*)malloc(15);
    }

    char FInput[15];                    //line 18-21 data storage and pointer initialization
    char SInput[15];
    char print[15];
    char regs[15], comms[100];

    int ax, bx, cx, dx, Given;          //Given = user input
    int count = 0;                      //initialization of registers and other variables
    int jumps = 0;
    int FTemp = 0;
    int STemp = 0;

    while(!feof(ptr)){                  //storing lines from the file to lines[]
        fgets(lines[count], 100, ptr);
        count++;
    }

    for(int i = 0; i < count; i++){     //this will essentially go through the whole file in terms of lines
        if(lines[i][0] == '\n'){        //continue if you see a blank line
            continue;
        }

        sscanf(lines[i], "%s", comms);  //checks the very first "command" in the line

        if(strcmp(comms, "mov") == 0){  //very large group of if-elseif-else statements corresponding to following command
            sscanf(lines[i], "%s %s %s", comms, FInput, SInput);    //taking the "strings" in the corresponding line with mov, and storing them in variables

            if(isalpha(FInput[0])){     //checks if letter, storing it into register
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {                    
                FTemp = atoi(FInput);   //if not letter, conversion to integer and storage
            }
                                        //storing into second register
            if(strcmp(SInput, "ax") == 0){
                ax = FTemp;
            }
            else if(strcmp(SInput, "bx") == 0){
                bx = FTemp;
            }
            else if(strcmp(SInput, "cx") == 0){
                cx = FTemp;
            }
            else if(strcmp(SInput, "dx") == 0){
                dx = FTemp;
            }
        }

        else if(strcmp(comms, "add") == 0){
            sscanf(lines[i], "%s %s %s", comms, FInput, SInput); //same concept as in move

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(strcmp(SInput, "ax") == 0){      //adding values and storage into corresponding registers
                ax += FTemp;
            }
            else if(strcmp(SInput, "bx") == 0){
                bx += FTemp;
            }
            else if(strcmp(SInput, "cx") == 0){
                cx += FTemp;
            }
            else if(strcmp(SInput, "dx") == 0){
                dx += FTemp;
            }
        }

        else if(strcmp(comms, "sub") == 0){     //same concept as in both mov and add
            sscanf(lines[i], "%s %s %s", comms, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(strcmp(SInput, "ax") == 0){      //subtracting values and storing
                ax -= FTemp;
            }
            else if(strcmp(SInput, "bx") == 0){
                bx -= FTemp;
            }
            else if(strcmp(SInput, "cx") == 0){
                cx -= FTemp;
            }
            else if(strcmp(SInput, "dx") == 0){
                dx -= FTemp;
            }
        }

        else if(strcmp(comms, "mul") == 0){
            sscanf(lines[i], "%s %s %s", comms, FInput, SInput);    //taking strings in the line and mapping them to specific variables (same thing)

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(strcmp(SInput, "ax") == 0){      //multiplication and storage
                ax *= FTemp;
            }
            else if(strcmp(SInput, "bx") == 0){
                bx *= FTemp;
            }
            else if(strcmp(SInput, "cx") == 0){
                cx *= FTemp;
            }
            else if(strcmp(SInput, "dx") == 0){
                dx *= FTemp;
            }
        }

        else if(strcmp(comms, "div") == 0){
            sscanf(lines[i], "%s %s %s", comms, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(strcmp(SInput, "ax") == 0){      //division and storage into registers
                ax = FTemp / ax;
            }
            else if(strcmp(SInput, "bx") == 0){
                bx = FTemp / bx;
            }
            else if(strcmp(SInput, "cx") == 0){
                cx = FTemp / cx;
            }
            else if(strcmp(SInput, "dx") == 0){
                dx = FTemp / dx;
            }
        }


        else if(strcmp(comms, "jmp") == 0){
            sscanf(lines[i], "%s %d", comms, &jumps); 
            i = jumps - 1;          //set i to jumps - 1 since the index starts at 0
        }

        else if(strcmp(comms, "jne") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp != STemp){     //checking to see if x != y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "je") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp == STemp){         //checking to see if x = y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "jge") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp >= STemp){         //check to see if x >= y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "jg") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp > STemp){          //check to see if x > y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "jle") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp <= STemp){         //check to see if x <= y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "jl") == 0){
            sscanf(lines[i], "%s %d %s %s", comms, &jumps, FInput, SInput);

            if(isalpha(FInput[0])){
                if(strcmp(FInput, "ax") == 0){
                    FTemp = ax;
                }
                else if(strcmp(FInput, "bx") == 0){
                    FTemp = bx;
                }
                else if(strcmp(FInput, "cx") == 0){
                    FTemp = cx;
                }
                else if(strcmp(FInput, "dx") == 0){
                    FTemp = dx;
                }
            } else {
                FTemp = atoi(FInput);
            }

            if(isalpha(SInput[0])){
                if(strcmp(SInput, "ax") == 0){
                    STemp = ax;
                }
                else if(strcmp(SInput, "bx") == 0){
                    STemp = bx;
                }
                else if(strcmp(SInput, "cx") == 0){
                    STemp = cx;
                }
                else if(strcmp(SInput, "dx") == 0){
                    STemp = dx;
                }
            } else {
                STemp = atoi(SInput);
            }

            if(FTemp < STemp){          //check to see if x < y
                i = jumps - 1;
            } else {
                continue;
            }
        }

        else if(strcmp(comms, "print") == 0){
            sscanf(lines[i], "%s %s", comms, print);

            if(strcmp(print, "ax") == 0){        
                printf("%d", ax);
            }
            else if(strcmp(print, "bx") == 0){
                printf("%d", bx);
            }
            else if(strcmp(print, "cx") == 0){
                printf("%d", cx);
            }
            else if(strcmp(print, "dx") == 0){
                printf("%d", dx);
            } else{
                printf("%d", atoi(print));
            }
        }

        else if(strcmp(comms, "read") == 0){
            sscanf(lines[i], "%s %s", comms, regs);

            printf("Enter the value: ");        //need user input
            scanf("%d", &Given);

            if(strcmp(regs, "ax") == 0){
                ax = Given;
            }
            else if(strcmp(regs, "bx") == 0){
                bx = Given;
            }
            else if(strcmp(regs, "cx") == 0){
                cx = Given;
            }
            else if(strcmp(regs, "dx") == 0){
                dx = Given;
            }
        }
    }

    for(int i = 0; i < 100; i++){       //freeing lines
        free(lines[i]);
    }
    printf("\n");
    fclose(ptr);        //close the file
}