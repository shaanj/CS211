#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int array[], int size){
    int i, key, j;
    for(i = 1; i < size; i++){
        key = array[i];
        j = i - 1;

        while(j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void RevInsertionSort(int array[], int size){
    int i, key, j;
    for(i = 1; i < size; i++){
        key = array[i];
        j = i - 1;

        while(j >= 0 && array[j] < key){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}


int main(int argc, char* argv[]) {
    FILE *ptr_file;                     
    ptr_file = fopen(argv[1], "r");     

    int i;
    int EC = 0;
    int OC = 0;                     
    int n;
    fscanf(ptr_file, "%d\n", &n); 

    int *arr = (int*) malloc(sizeof(int) * n);
    int *even = (int*) malloc(sizeof(int) * n);
    int *odd = (int*) malloc(sizeof(int) * n);
                             
    for(i = 0; i < n; i++) {
    fscanf(ptr_file,"%d", &arr[i]);
        if(arr[i] % 2 != 0){
            odd[OC] = arr[i];
            OC++;
        } else {
            even[EC] = arr[i];
            EC++;
        }

    }

    fclose(ptr_file);

    InsertionSort(even, EC);
    RevInsertionSort(odd, OC);

    for(i = 0; i < EC; i++){
        printf("%d\t", even[i]);
    }

    for(i = 0; i < OC; i++){
        if(odd[i] == 0){
            continue;
        }
        printf("%d\t", odd[i]);
    }
        printf("\n");

    free(even);
    free(odd);
    free(arr);
    return 0;
}
