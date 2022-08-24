#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printMatrix(double **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        printf("\n");
        for (int j = 0; j < col; j++){
            printf("%lf ", matrix[i][j]);
        }
    }
    printf("\n");
}

double **createMatrix(int row, int col){
    double** matrix = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++){
        matrix[i] = (double *)malloc(col * sizeof(double));
    }
    return matrix;
}


void fillMatrix(double **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("Enter entry row: %d, col: %d: ", i + 1, j + 1);
            scanf("%lf", &matrix[i][j]);
        }
        printf("\n");
    }
}

void swapRows(double **matrix, int row1, int row2, int col){
    double temp;
    for (int i = 0; i < col; i++){
        temp = matrix[row2][i];
        matrix[row2][i] = matrix[row1][i];
        matrix[row1][i] = temp;
    }
}

void swapRowOfZeros(double **matrix, int row, int col){
    int counter = 0;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (matrix[i][j] < 0.001 && matrix[i][j] > -0.001){
                counter++;
            }
        }
        if (counter == col){
            for (int idx = 0; idx < row - i - 1; idx++){
                swapRows(matrix, idx + i, idx + i + 1, col);
            }
            printf("\nswapRowofZeros\n");
        }
        counter = 0;
    }
    
}

void columnsToZero(double **matrix, int row, int col, int entry_row, int entry_col){
    double multiplier;
    for (int i = 0; i < row; i++){
        if (i != entry_row && matrix[i][entry_col] != 0){
            multiplier = matrix[i][entry_col];
            
            for (int j = 0; j < col; j++){
                matrix[i][j] = matrix[i][j] - multiplier * matrix[entry_row][j];

            }
        }
    }
}

void gaussianEliminateActual(double **matrix, int row, int col){
    swapRowOfZeros(matrix, row, col);
    int rows_counter = 0;
    int j;
    bool found;
    double saved_entry;
    for (int i = 0; i < col; i++){
        j = rows_counter;
        found = false;

        while(j < row && found == false){
            if (matrix[j][i] > 0.001 || matrix[j][i] < -0.001){         // if nonzero entry
                if (rows_counter != j){                                     // don't want to swap the same row
                    swapRows(matrix, rows_counter, j, col);
                }

                // divide by 1 ... etc.                                 // divide nonzero entry by 1
                saved_entry = matrix[rows_counter][i];
                for (int i_col = 0; i_col < col; i_col++){              // add / subtract s.t. other entries in the column is 0
                    matrix[rows_counter][i_col] = matrix[rows_counter][i_col] / saved_entry;
                    
                }                                                        
                columnsToZero(matrix, row, col, rows_counter, i);

                rows_counter++;                 // default row to swap
                found = true;                   // exit while loop once nonzero entry is found (exit upon finding the first leading 1)
            }
            
            else {
                j++;
            }
            
            // if no nonzero entry, move to next column by exiting while loop and returning to outer for loop

        }
    }
}

int main(){
    /* PROMPT VECTOR ROW AND COL */
    int row;
    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("\n");

    int col;
    printf("Enter the number of columns: ");
    scanf("%d", &col);
    printf("\n");

    /* INIT MATRIX ENTRIES */
    double **matrix = createMatrix(row, col);
    fillMatrix(matrix, row, col);
    printMatrix(matrix, row , col);

    gaussianEliminateActual(matrix, row, col);
    printMatrix(matrix, row, col);
    return 0;
}
