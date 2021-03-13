#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int INPalindrome(int arr[])                 //this method checks if the given int[] IS or IS NOT palindromic 
{
    int Bflag = 0;                          //Bflag is used as a boolean flag by either having 1 or 0 to denote Is/Is Not
    for(int j = 0; j < 8; j++){             //0 - 8 to go through the corresponding indexes of the array   
        if (arr[j] != arr[15 - j]){         //if for example index 2 and index 13 dont match, it is not a palindrome
            Bflag = 0;
            break;                          //first mismatch means that the rest don't need to be checked and can break
        } else { 
            Bflag = 1; 
        }
    }
    return Bflag;                           //returns the result of either it is 1 or 0, essentially is/is not
}

int main(int argc, char* argv[])
{
    int given;
    char inArr[30];                     
    strcpy(inArr, argv[1]);
    sscanf(inArr, "%d", &given);

    int bin[16] = {0};                      //array of size 16 to be able to take in input with 16 bits

    for(int i = 15; i >= 0; i--){
        bin[i] = given % 2;
        given = given / 2;
    }

    int INPal = INPalindrome(bin);          //int variable to take in the result of the above method that finds if a given array is a palindrome
    if((INPal) == 0){                       //if the result is 0, then the given was not palindromic in 16bit binary representation
        printf("Not-Palindrome\n");
    }
    if((INPal) == 1){
        printf("Is-Palindrome\n");         //if the result is 1, then the given was palindromic.
    }
return 0;
}
