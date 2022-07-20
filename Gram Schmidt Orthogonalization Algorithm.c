#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dotProd(double **vectorMatrix1, double** vectorMatrix2, int dimension, int vector1, int vector2){
    double dotProduct = 0;
    for (int col = 0; col < dimension; col++){
        dotProduct += vectorMatrix1[vector1][col] * vectorMatrix2[vector2][col];
    }
    return dotProduct;
}

double *allocateVector(int dimension){
    double* vectorVariable = (double*)malloc(dimension * sizeof(double));
    return vectorVariable;
}

void vectorAddition(double *vector1, double *vector2, int dimension, double *vectorVariableName){
    for (int col = 0; col < dimension; col++){
        vectorVariableName[col] = vector1[col] + vector2[col];
    }
}

void vectorSubtraction(double **vectorMatrix, double *vector, int dimension, int vector1, double **vectorMatrixVariableName, int k){
    for (int col = 0; col < dimension; col++){
        vectorMatrixVariableName[k][col] = vectorMatrix[vector1][col] - vector[col];
    }
}

void vectorScalarMultiplication(double **vectorMatrix, int dimension, int vectorToMultiply, double *vectorVariableName, double scalar){
    for (int col = 0; col < dimension; col++){
        vectorVariableName[col] = vectorMatrix[vectorToMultiply][col] * scalar;
    }
}

double vectorMagnitude(double **vectorMatrix, int dimension, int vectorToMagnitude){
    double squaredSum = 0.0;
    for (int col = 0; col < dimension; col++){
        squaredSum += vectorMatrix[vectorToMagnitude][col] * vectorMatrix[vectorToMagnitude][col];
    }
    return sqrt(squaredSum);
}

void unitVector(double **vectorMatrix, int dimension, int vectorToUnitize, double **vectorVariableName){
    double magnitude = vectorMagnitude(vectorMatrix, dimension, vectorToUnitize);
    for (int col = 0; col < dimension; col++){
        vectorVariableName[vectorToUnitize][col] = vectorMatrix[vectorToUnitize][col] / magnitude;
    }
}

double **createVectorMatrix(int dimension, int numberOfVectors){
    // DYNAMICALLY ALLOCATE MEMORY
    double** vectorMatrix = (double**)malloc(numberOfVectors * sizeof(double*));
    for (int i = 0; i < numberOfVectors; i++){
        vectorMatrix[i] = (double*)malloc(dimension * sizeof(double));
    }
    return vectorMatrix;
}

void **fillVectorMatrix(int dimension, int numberOfVectors, double **vectorMatrix){
    for (int row = 0; row < numberOfVectors; row++){
        printf("Enter entries for vector %d: ", row + 1);
        printf("\n");
        for (int col = 0; col < dimension; col++){
            printf("Vector %d, Entry %d: ", row + 1, col + 1);
            scanf("%lf", &vectorMatrix[row][col]);
            printf("\n");
        }
    }
}

void gramSchmidt(double **vectorMatrix, double **gramSchmidtVecMat, double **gramSchmidtUnitVecMat, int dimension, int numberOfVectors){

    // ALLOCATE VECTOR VARIABLE FOR SCALAR MULTIPLICATION STEP
    double *allocateVecVarScalarMult = allocateVector(dimension);

    // ALLOCATE VECTOR ADDITION STEP
    double *openVar = allocateVector(dimension);

    // INIT VARIABLES
    double dotProduct;
    double magnitudeSquared;
    double division;
    
    // ITERATION FOR EACH VECTOR
    for (int k = 1; k <= numberOfVectors; k++){
        for (int col = 0; col < dimension; col++){
            gramSchmidtVecMat[k-1][col] = vectorMatrix[k-1][col];
        }

        // IF THERE ARE MORE THAN 1 VECTOR
        if (k > 1){
            
            // INIT OPENVAR ENTRIES TO 0
            for (int iteration = 0; iteration < dimension; iteration++){
                openVar[iteration] = 0;
            }

            // ITERATION OF SUM OF INNER PRODUCTS 
            for (int i = 1; i < k; i++){
                dotProduct = dotProd(vectorMatrix, gramSchmidtVecMat, dimension, k-1, i-1);
                magnitudeSquared = fabs(vectorMagnitude(gramSchmidtVecMat, dimension, i-1) * vectorMagnitude(gramSchmidtVecMat, dimension, i-1));
                division = dotProduct / magnitudeSquared;
                vectorScalarMultiplication(gramSchmidtVecMat, dimension, i-1, allocateVecVarScalarMult, division);
                vectorAddition(openVar, allocateVecVarScalarMult, dimension, openVar);
            }
            vectorSubtraction(vectorMatrix, openVar, dimension, k-1, gramSchmidtVecMat, k-1);
        }
    }

    int numberOfZeros;

    // FOR EACH ROW, CHECK IF ALL ENTRIES ARE 0
    for (int row = 0; row < numberOfVectors; row++){
        numberOfZeros = 0;
        for (int col = 0; col < dimension; col++){

            // IF ENTRY IS 0
                // THEN INCREMENT numberOfZeros
            if (fabs(gramSchmidtVecMat[row][col]) < 0.000001){
                numberOfZeros++;    
                gramSchmidtUnitVecMat[row][col] = 0;
            }
        }

        // IF THE NUMBER OF ZEROS IN THE ROW DNE THE TOTAL NUMBER OF ENTRIES IN THE ROW
            // THEN UNITIZE THE ROW
        if (numberOfZeros != dimension){
            unitVector(gramSchmidtVecMat, dimension, row, gramSchmidtUnitVecMat);
        }
    }
}

void printMatrix(double **vectorMatrix, int dimension, int numberOfVectors){
    for (int row = 0; row < numberOfVectors; row++){
        printf("\nVector %d: ", row + 1);
        for (int col = 0; col < dimension; col++){
            printf("%lf ", vectorMatrix[row][col]);
        }
    }
}

int main(){
    
    // PROMPT VECTOR DIMENSION (SIZE) 
    int dimension;
    printf("Enter the vector space dimension: ");
    scanf("%d", &dimension);
    printf("\n");

    // PROMPT NUMBER OF VECTORS
    int numberOfVectors;
    printf("Enter the number of vectors: ");
    scanf("%d", &numberOfVectors);
    printf("\n");

    // INIT MATRICES WHERE EACH ROW IS A VECTOR AND COLUMN AS VECTOR ENTRY
        // NUMBER OF ROWS = NUMBER OF VECTORS
        // NUMBER OF COLUMNS = VECTOR DIMENSION
    double **vectorMatrix = createVectorMatrix(dimension, numberOfVectors);
    double **gramSchmidtVecMat = createVectorMatrix(dimension, numberOfVectors);
    double **gramSchmidtUnitVecMat = createVectorMatrix(dimension, numberOfVectors);
    
    // PROMPT ORIGINAL VECTOR ENTRIES
    fillVectorMatrix(dimension, numberOfVectors, vectorMatrix);

    // CONDUCT GRAM-SCHMIDT ORTHOGONALIZATION PROCESS
    gramSchmidt(vectorMatrix, gramSchmidtVecMat, gramSchmidtUnitVecMat, dimension, numberOfVectors);
    
    // PRINT THE PROCESSED VECTORS
    printf("Set of Orthogonalized Vectors:");
    printMatrix(gramSchmidtVecMat, dimension, numberOfVectors);
    printf("\n\nSet of Orthonormal Vectors:");
    printMatrix(gramSchmidtUnitVecMat, dimension, numberOfVectors);

    return 0;
}
