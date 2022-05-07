#include <stdio.h>
#include <stdlib.h>

int twoByTwo(int **twoByTwoMatrix){
    int determinant = twoByTwoMatrix[0][0] * twoByTwoMatrix[1][1] - twoByTwoMatrix[0][1] * twoByTwoMatrix[1][0];
    return determinant;
}

void createDetStorage(int determinant){
    int* detStorage = (int*)malloc()
}

int **createMatrix(){

    // PROMPT SQUARE MATRIX SIZE
    int matrixSize;
    printf("Enter the matrix size: ");
    scanf("%d", &matrixSize);
    printf("\n");

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
    int **createMatrixPtr = createMatrix();
    printf("%d\n", twoByTwo(createMatrixPtr));

    // int testMatrix[2][2] = {{1,2},{3,4}};
    // printf("%d\n", twoByTwo(testMatrix));
    return 0;
}