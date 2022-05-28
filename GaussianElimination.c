#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int **subtractRows(int **matrix, int rowSize, int minuendRow, int subtrahendRow){
    for (int i = 0; i < rowSize; i++){
        matrix[minuendRow][i] = matrix[minuendRow][i] - matrix[subtrahendRow][i];
    }
    return matrix;

}

int **addRows(int **matrix, int rowSize, int summandRow, int rowToAdd){
    for (int i = 0; i < rowSize;  i++){
        matrix[summandRow][i] = matrix[summandRow][i] + matrix [rowToAdd][i];
    }
    return matrix;

}

int **multiplyRow(int **matrix, int rowSize, int rowMultiply, int factor){
    for (int i = 0; i < rowSize; i++){
        matrix[rowMultiply][i] = matrix[rowMultiply][i] * factor;
    }
    return matrix;

}

int **swapRows(int **matrix, int rowSize, int row1, int row2){
    int temp;
    for (int i = 0; i < rowSize; i++){
        temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
    return matrix;
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

bool isZeroMatrix(int **matrix, int rowSize, int colSize){
    for (int row = 0; row < rowSize; row++){
        for (int col = 0; col < colSize; col++){
            if (matrix[row][col] != 0){;
                return false;
            }
        }
    }
    return true;
}

int **gaussianEliminate(int **matrix, int rowSize, int colSize){
    
    // ZERO MATRIX
    if (isZeroMatrix(matrix, rowSize, colSize)){
        return matrix;
    }

    // NONZERO MATRIX
    // find first column from left containing a nonzero
    int col = 0, row;
    bool nonZero = false;

    int j;
    bool condition;

    int savedNumber;

    for (int iteration = 0; iteration < rowSize; iteration++){
        // while (col < colSize && nonZero == false){
        //     row = iteration;
        //     while (row < rowSize && nonZero == false){
        //         if (matrix[row][col] != 0){
        //             nonZero = true;
        //         }
        //         else{
        //             row++;
        //         }
        //     }
        //     col++;
        // }

        // swapRows(matrix, rowSize, row, iteration);    
        
        j = 0;
        condition = false;

        while (j < colSize && condition == false){
            if (matrix[iteration][j] != 0){
                multiplyRow(matrix, rowSize, iteration, 1 / matrix[iteration][j]);  // achieve leading one
                condition = true;
            }
            else{
                j++;
            }
        }
        
        for (int k = 0; k < rowSize; k++){          // iterate through each row
            if (k != iteration){
                if (matrix[k][j] != 0){
                    savedNumber = matrix[k][j];
                    multiplyRow(matrix, rowSize, iteration, savedNumber);
                    subtractRows(matrix, rowSize, k, iteration);
                    multiplyRow(matrix, rowSize, iteration, 1 / savedNumber); // unmultiply
                }

            }
            // else { do nothing }
        }
    }

    return matrix;
}


int main(){

    // PROMPT MATRIX SIZE
    int rowSize, colSize;
    printf("Enter the row size: ");
    scanf("%d", &rowSize);
    printf("\n");

    printf("Enter the col size: ");
    scanf("%d", &colSize);
    printf("\n");

    // CREATE MATRIX 2D DYNAMIC ARRAY
    int **matrix = createMatrix(rowSize, colSize);

    // APPLY GAUSSIAN ELIMINATION TO BRING MATRIX INTO RREF
    gaussianEliminate(matrix, rowSize, colSize);

    // PRINT RREF MATRIX
    printf("\nRREF:\n");
    for (int row = 0; row < rowSize; row++){
        for (int col = 0; col < colSize; col++){
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }

    free(matrix);

    return 0;
}
