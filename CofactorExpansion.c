/* This program takes matrix size and matrix entry inputs from the user
   It calculates the determinant and prints the value */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int **createMatrix(int matrixSize){  
    
    // DYNAMICALLY ALLOCATE 2D ARRAY
    int** matrix = (int**)malloc(matrixSize * sizeof(int*));    
    for (int i = 0; i < matrixSize; i++){
        matrix[i] = (int*)malloc(matrixSize * sizeof(int));
    }

    // STORE MATRIX ENTRIES
    for (int row = 0; row < matrixSize; row++){
        for (int col = 0; col < matrixSize; col++){
            printf("Row %d Column %d = ", row, col);
            scanf("%d", &matrix[row][col]);
        }
    }
    return matrix;
}


int laplaceExpand(int matrixSize, int **matrix, int *guard){
   
    // BASE CASES
    if (matrixSize == 1){
        return matrix[0][0];
    }
    if (matrixSize == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    // RECURSIVE CASE
    int originalCol, row, col, totalDet = 0, sign = 1; 

    // Allocate memory for sub-matrix
    int** subMatrix = (int**)malloc((matrixSize - 1) * sizeof(int*));    
    for (int i = 0; i < matrixSize - 1; i++){
        subMatrix[i] = (int*)malloc((matrixSize - 1) * sizeof(int));
    }
    
    // Guard condition
    if (subMatrix == NULL){
        *guard = 0;
        return 0;
    }

    // Copy orginal matrix into sub-matrix
    for (originalCol = 0; originalCol < matrixSize; originalCol++){
        for (row = 1; row < matrixSize; row++){
            for (col = 0; col < originalCol; col++){
                subMatrix[row - 1][col] = matrix[row][col];
            }
            for (col = originalCol + 1; col < matrixSize; col++){
                subMatrix[row - 1][col - 1] = matrix[row][col];
            }
        }

        int recurDet = laplaceExpand(matrixSize - 1, subMatrix, guard);
        if (guard == NULL){
            free(subMatrix);
            return 0;
        }

        // Multiply by coefficient
        totalDet += sign * matrix[0][originalCol] * recurDet;
        sign *= -1;
    }
    free (subMatrix);
    return totalDet;
}


int main(){

    // PROMPT MATRIX SIZE
    int matrixSize;
    printf("Enter the matrix size: ");
    scanf("%d", &matrixSize);
    printf("\n");

    // CREATE MATRIX 2D DYNAMIC ARRAY
    int **matrix = createMatrix(matrixSize);

    // APPLY LAPLACE EXPANSION
    int guard = 1;
    int determinant = laplaceExpand(matrixSize, matrix, &guard);

    if(guard) {
        printf("Determinant = %d\n", determinant);
    }
    free(matrix);
    return 0;
}
