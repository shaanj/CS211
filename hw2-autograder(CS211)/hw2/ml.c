/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transposed(X)*X) * transposed(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// all methods declarations
double **multipliedMatrix(double **multiplied, double **matA, double **matB, int r1, int c1, int r2, int c2);
double **transposedMatrix(double **transposed, double **matA, int row, int col);
double **inverseMatrix(double **matI, double **matA, int dimension);

// main method starts here
int main(int argc, char **argv)
{
    FILE *file;
    double ans = 0;
    int col, row, num;

    file = fopen(argv[1], "r");
    if(file == NULL){
        return 0;
    }

    fscanf(file, "%d\n%d", &col, &row);
    double **matA = (double **)malloc(sizeof(double *) * row);
    double **matB = (double **)malloc(sizeof(double *) * row);
    double **inversedA = (double **)malloc(sizeof(double *) * (col + 1));
    double **inversedB = (double **)malloc(sizeof(double *) * (col + 1));
    double **transposed = (double **)malloc(sizeof(double *) * (col + 1));
    double **multiplied = (double **)malloc(sizeof(double *) * (col + 1));
    double **other = (double **)malloc(sizeof(double *) * (col + 1));
    double **weight = (double **)malloc(sizeof(double *) * (col + 1));

    for(int i = 0; i < row; i++){
        matA[i] = malloc((col + 1) * sizeof(double));
        matB[i] = malloc(sizeof(double));
    }

    for(int i = 0; i < col + 1; i++) {
        inversedA[i] = malloc((col + 1) * 2 * sizeof(double));
        inversedB[i] = malloc((col + 1) * sizeof(double));
        transposed[i] = malloc((row) * sizeof(double));
        multiplied[i] = malloc((col + 1) * sizeof(double));
        other[i] = malloc((row) * sizeof(double));
        weight[i] = malloc(sizeof(double));
    }

    for(int x = 0; x < row; x++){
        for(int y = 0; y < col + 2; y++){
            if(y == 0){
                matA[x][y] = 1;
            } else {
                double temp = 0;
                fscanf(file, "%lf,", &temp);
                if (y == col + 1){
                    matB[x][0] = temp;
                } else {
                    matA[x][y] = temp;
                }
            }
        }
    }

    transposed = transposedMatrix(transposed, matA, row, col + 1);
    multiplied = multipliedMatrix(multiplied, transposed, matA, col + 1, row, row, col + 1);
    inversedA = inverseMatrix(inversedA, multiplied, col + 1);

    for(int x = 0; x < col + 1; x++){
        for (int y = col + 1; y < (col + 1) * 2; y++){
            inversedB[x][y - col - 1] = inversedA[x][y];
        }
    }

    other = multipliedMatrix(other, inversedB, transposed, col + 1, col + 1, col + 1, row);
    weight = multipliedMatrix(weight, other, matB, col + 1, row, row, 1);

    file = fopen(argv[2], "r");
    fscanf(file, "%d", &num);
    if (file == NULL){
        return 0;
    }

    for(int x = 0; x < num; x++){
        ans = weight[0][0];
        for (int y = 0; y < col; y++){
            double temp = 0;
            fscanf(file, "%lf,", &temp);
            ans += (weight[y + 1][0] * temp);
        }
        printf("%0.0lf\n", ans);
    }

    for(int i = 0; i < row; i++){
        free(matA[i]);
        free(matB[i]);
    }

    for(int i = 0; i < col + 1; i++){
        free(transposed[i]);
        free(multiplied[i]);
        free(inversedA[i]);
        free(inversedB[i]);
        free(other[i]);
        free(weight[i]);
    }

    free(transposed);
    free(multiplied);
    free(inversedA);
    free(inversedB);
    free(other);
    free(weight);
    free(matA);
    free(matB);
    return 0;
}

double **multipliedMatrix(double **multiplied, double **matA, double **matB, int r1, int c1, int r2, int c2){
    double product;
    for (int x = 0; x < r1; x++){
        for (int y = 0; y < c2; y++){
            product = 0;
            for (int z = 0; z < r2; z++){
                product += matA[x][z] * matB[z][y];
            }
            multiplied[x][y] = product;
        }
    }
    return multiplied;
}

double **transposedMatrix(double **transposed, double **matA, int rows, int columns){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            transposed[j][i] = matA[i][j];
        }
    }
    return transposed;
}

double **inverseMatrix(double **inversed, double **matrix, int rows){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            inversed[i][j] = matrix[i][j];
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = rows; j < rows * 2; j++){
            if (j == (i + rows)){
                inversed[i][j] = 1;
            } else{
                inversed[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            if(i != j){
                double ratio = inversed[j][i] / inversed[i][i];
                for (int k = 0; k < 2 * rows; k++){
                    inversed[j][k] = inversed[j][k] - ratio * inversed[i][k];
                }
            }
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = rows; j < 2 * rows; j++){
            inversed[i][j] = inversed[i][j] / inversed[i][i];
        }
    }
    return inversed;
}