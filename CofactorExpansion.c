#include <stdio.h>
#include <stdlib.h>

// FUNCTION DECLARATIONS
int factorial(int value);
void cofactorExpand(int size, int **matrix);
int twoByTwo(int **twoByTwoMatrix);
int twoByTwo(int **twoByTwoMatrix);
int *createDetStorage(int matrixSize);
int **createMatrix(int matrixSize);
void storeDet(int *detStorage, int position, int determinant);
int **makeRemainderCopy(int matrixSize, int **originalMatrix, int rowIgnore, int colIgnore);



int factorial(int value){
    unsigned long long fact = 1;
    for (int i = 1; i <= value; i++) {
        fact *= i;
    }
}

int **makeRemainderCopy(int matrixSize, int **originalMatrix, int rowIgnore, int colIgnore){

    // DYNAMICALLY ALLOCATE 2D ARRAY
    int** copiedMatrix = (int**)malloc((matrixSize - 1)* sizeof(int*));    
    for (int i = 0; i < matrixSize - 1; i++){
        copiedMatrix[i] = (int*)malloc((matrixSize - 1) * sizeof(int));
    }

    // COPY ORIGINAL MATRIX ELEMENTS
    int copiedMatrixRow = 0, copiedMatrixCol = 0;
    for (int row = 1; row < matrixSize; row++){
        for (int col = 0; col < matrixSize; col++){
            if (!(col == colIgnore)){
                copiedMatrix[copiedMatrixRow][copiedMatrixCol] == originalMatrix[row][col];
                copiedMatrixRow++;
                copiedMatrixCol++;
            }
        }
    }

    return copiedMatrix;
}

void cofactorExpand(int size, int **matrix){

    // BASE CASE
    if (size == 2){

    }

    // RECURSIVE CASE
    else{
        int remainingRows = sizeof(matrix) / sizeof(matrix[0]);     // number of rows of the remaining matrix
        for(int i = 0; i < remainingRows; i++){         // to iterate through the remaining size of array
            
        }
    }
}


void storeDet(int *detStorage, int position, int determinant){
    *(detStorage + position) = determinant;
}

int twoByTwo(int **twoByTwoMatrix){
    int determinant = twoByTwoMatrix[0][0] * twoByTwoMatrix[1][1] - twoByTwoMatrix[0][1] * twoByTwoMatrix[1][0];
    return determinant;
}

int *createDetStorage(int matrixSize){
    int* detStorage = (int*)malloc(factorial(matrixSize) * sizeof(int));
    return detStorage;
}

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



int main(){
    
    // PROMPT SQUARE MATRIX SIZE
    int matrixSize;
    printf("Enter the matrix size: ");
    scanf("%d", &matrixSize);
    printf("\n");



    int **createMatrixPtr = createMatrix(matrixSize);
    printf("%d\n", twoByTwo(createMatrixPtr));

    // int testMatrix[2][2] = {{1,2},{3,4}};
    // printf("%d\n", twoByTwo(testMatrix));
    return 0;
}
