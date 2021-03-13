#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const int VarSize = 50;
const int InSize = 100;
void notimportant(FILE* given);
void alsonotimportant(char given[], char gimme[]);

void notimportant(FILE* given){
    fscanf(given, "\n");
}

void alsonotimportant(char given[], char gimme[]){
    strcpy(given, gimme);
}

unsigned long hash(unsigned char *str){
        unsigned long hash = 5381;
        int c;
        while (c = *str++)
            hash = ((hash << 5) + hash) + c; 

        return hash;
}

int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
	int InVars;
	fscanf(fp, "INPUTVAR %d ", &InVars);

	int linecount = pow(2, InVars);
	int InTable[linecount][InVars];

	for(int i = 0; i < linecount; i++){
		int x = i;
		for(int j = InVars; j > 0; j--){
			int temp = 1;
			if((temp&x) == 0){
				InTable[i][j-1] = 0;
			} else {
				InTable[i][j-1] = 1;
			}
			x = x>>1;
		}
	}
	
	char InNames[InVars][VarSize];
	for(int i = 0; i < InVars; i++){
		fscanf(fp, "%s ", InNames[i]);
	}
	notimportant(fp);

	int OutVars;
	fscanf(fp, "OUTPUTVAR %d ", &OutVars);

	int OutTable[linecount][OutVars];
	for(int i = 0; i < linecount; i++){
		for(int j = 0; j < OutVars; j++){
			OutTable[i][j] = 0;
		}
	}

	char OutNames[OutVars][VarSize];
	for(int i = 0; i < OutVars; i++){
		fscanf(fp, "%s ", OutNames[i]);
	}
	notimportant(fp);
	
	char comms[6];
	char FirstIn[InSize];
	char SecIn[InSize];
	char ThirdIn[InSize];
	int TTable[linecount][InSize];
	char TNames[InSize][VarSize];

	for(int i = 0; i < InSize; i++){
		strcpy(TNames[i], "");
	}
	
	int BigOne = fscanf(fp, "%s%s%s", comms, FirstIn, SecIn);
	int Finale = 0;

	while(BigOne == 3){
		int In1[linecount];
		int In2[linecount];
		int GiveOut[linecount];
		char output[10];

		if(strcmp("NOT", comms) != 0){
			BigOne++;
			fscanf(fp, "%s", ThirdIn);
		}

		if(BigOne == 3){
            for(int i = 0; i < Finale; i++){
				if(strcmp(FirstIn, TNames[i]) == 0){
					for(int j = 0; j < linecount; j++){
						In1[j] = TTable[j][i];
					}
				}
			}
			for(int i = 0; i < InVars; i++){
				if(strcmp(FirstIn, InNames[i]) == 0){
					for(int j = 0; j < linecount; j++){
						In1[j] = InTable[j][i];
					}
				}
			}
			alsonotimportant(output, SecIn);
		} else {
            for(int i = 0; i < Finale; i++){
				if(strcmp(FirstIn, TNames[i]) == 0){
					for(int j = 0; j < linecount; j++){
						In1[j] = TTable[j][i];
					}
				} 
                else if(strcmp(SecIn, TNames[i]) == 0){
                    for(int j = 0; j < linecount; j++){
						In2[j] = TTable[j][i];
					}
                }
			}

			for(int i = 0; i < InVars; i++){
				if(strcmp(FirstIn, InNames[i]) == 0){
					for(int j = 0; j < linecount; j++){
						In1[j] = InTable[j][i];
					}
				}
                else if(strcmp(SecIn, InNames[i]) == 0){
					for(int j = 0; j < linecount; j++){
						In2[j] = InTable[j][i];
					}
				}
			}
			alsonotimportant(output, ThirdIn);
		}
		
		switch (hash(comms)){     //switch case to apply to the logic gates(AND, OR, etc.)
        case 193464630:     //NOT into the hash function is 193464630
            for(int i = 0; i < linecount; i++){
                if(In1[i] == 1){
                    GiveOut[i] = 0;
                } else {
                    GiveOut[i] = 1;
                }
            }
            break;

        case 193450424:     //AND into the hash function is 193450424
            for(int i = 0; i < linecount; i++){
                GiveOut[i] = In1[i]&In2[i];
            }
            break;

        case 6384317414:          //NAND into the hash function is 6384317414
            for(int i = 0; i < linecount; i++){
                GiveOut[i] = In1[i]&In2[i];
            }
            for(int i = 0; i < linecount; i++){
                if(GiveOut[i] == 1){
                    GiveOut[i] = 0;
                } else {
                    GiveOut[i] = 1;
                }
            }
            break;

        case 5862598:       //OR into the hash function is 5862598 
            for(int i = 0; i < linecount; i++){
                GiveOut[i] = In1[i]|In2[i];
            }
            break;  

        case 193464628:         //NOR into the hash function returned 193464628
            for(int i = 0; i < linecount; i++){
                GiveOut[i] = In1[i]|In2[i];
            }
            for(int i = 0; i < linecount; i++){
                if(GiveOut[i] == 1){
                    GiveOut[i] = 0;
                } else {
                    GiveOut[i] = 1;
                }
            }
            break;

        case 193475518:     //XOR into the hash function returned 193475518
            for(int i = 0; i < linecount; i++){
                GiveOut[i] = In1[i]^In2[i];
            }
            break;

        default:        //DEFAULT CASE
            break;
        }
		
		bool outputCopied = true;
		for(int i = 0; i < OutVars; i++){
			if(strcmp(output, OutNames[i]) == 0){
				for(int j = 0; j < linecount; j++){	
					OutTable[j][i] = GiveOut[j];
				}
				outputCopied = false;
			} else {
                alsonotimportant(TNames[Finale], output);
			    for(int i = 0; i < linecount; i++){
				    TTable[i][Finale] = GiveOut[i];
			    }
			    Finale++;
                }
		}
		BigOne = fscanf(fp, "%s%s%s\n", comms, FirstIn, SecIn); 
	}

	for(int i = 0; i < linecount; i++){
		for(int j = 0; j < InVars; j++){
			printf("%d ", InTable[i][j]);
		}
		for(int j = 0; j < OutVars; j++){
			printf("%d ", OutTable[i][j]);
		}
		printf("\n");
	}		
}