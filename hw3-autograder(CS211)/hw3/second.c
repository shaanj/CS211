#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   unsigned short given = atoi(argv[1]);       //input is taken as command line argument, not data from a file as usual
   unsigned short pairs = 0;
   unsigned short Pbit = 0; 
   unsigned short Cbit, ones; 
   
   while(given){                                //while the given number still has bits that can be read going to the right
       Cbit = given & 01;      
       if(Pbit && Cbit){                        //if the current and previous bit match and result in 11, the pair count increases
           pairs++;
           Pbit = 0;                            //reset the previous bit to be equal to 0, if a pair is found
       } else {
           Pbit = Cbit;                         //previous bit takes the value of the current bit
       }
       if(Cbit){                       
           ones++;
       }
       given >>= 1;                             //bit shift over 1 to the right
   }
   
   //printing out if the number has an even or odd amount of pairs of "11"s in their binary representation
   if(ones % 2 == 0){               
       printf("Even-Parity\t%d\n", pairs);
   } else {
       printf("Odd-Parity\t%d\n", pairs);
   }       
return 0;
}   
