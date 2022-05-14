#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int **subtractRows(int **matrix, int rowSize, int colSize, int minuendRow, int subtrahendRow){


}

int **addRows(int **matrix, int rowSize, int colSize, int summandRow, int rowToAdd){


}

int **multiplyRow(int **matrix, int rowSize, int colSize, int rowMultiply, int factor){


}

int **swapRows(int **matrix, int rowSize, int colSize, int row1, int row2){

    
}

int **createMatrix(int rowSize, int colSize){
    
    // DYNAMIC ALLOCATE 2D ARRAY
    int **matrix = (int**)malloc(rowSize * sizeof(int*));
    for (int i = 0; i < colSize; i++){
        matrix[i] = (int*)malloc(colSize * sizeof(int));
    }

    // STORE MATRIX ENTRIES
    for (int row = 0; row < rowSize; row++){
        for (int col = 0; col < colSize; col++){
            printf("Row %d Column %d = ", row, col);
            scanf("%d", &matrix[row][col]);
        }
    }
    return matrix;
}

bool zeroMatrix(int **matrix, int rowSize, int colSize){
    for (int row; row < rowSize; row++){
        for (int col; col < colSize; col++){
            if (matrix[row][col] != 0){
                return false;
            }
        }
    }
    return true;
}

int gaussianEliminate(int **matrix, int rowSize, int colSize){
    
    // ZERO MATRIX
    if (zeroMatrix(matrix, rowSize, colSize)){
        return matrix;
    }

    // NONZERO MATRIX




}


int main(){

    // PROMPT MATRIX SIZE
    int rowSize, colSize;
    printf("Enter the row size: ");
    scanf("%d", rowSize);
    printf("\n");

    printf("Enter the col size: ");
    scanf("%d", colSize);
    printf("\n");

    // CREATE MATRIX 2D DYNAMIC ARRAY
    int **matrix = createMatrix(rowSize, colSize);

    // APPLY GAUSSIAN ELIMINATION TO BRING MATRIX INTO RREF


    return 0;
}
