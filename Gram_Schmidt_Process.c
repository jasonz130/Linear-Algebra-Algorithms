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
    //Dynamically allocate memory
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
    
    for (int k = 1; k <= numberOfVectors; k++){
        for (int col = 0; col < dimension; col++){
            gramSchmidtVecMat[k-1][col] = vectorMatrix[k-1][col];
        }

        if (k > 1){
            
            // INIT OPENVAR ENTRIES TO 0
            for (int iteration = 0; iteration < dimension; iteration++){
                openVar[iteration] = 0;
            }

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

    int counter;
    for (int row = 0; row < numberOfVectors; row++){
        counter = 0;
        for (int col = 0; col < dimension; col++){
            if (fabs(gramSchmidtVecMat[row][col]) < 0.000001){      // IF 0
                counter++;    
                gramSchmidtUnitVecMat[row][col] = 0;

            }
        }
        if (counter != dimension){      // IF NOT A ROW OF 0s
            unitVector(gramSchmidtVecMat, dimension, row, gramSchmidtUnitVecMat);
        }
    }
}

int main(){
    int dimension;
    printf("Enter the vector space dimension: ");
    scanf("%d", &dimension);
    printf("\n");

    int numberOfVectors;
    printf("Enter the number of vectors: ");
    scanf("%d", &numberOfVectors);
    printf("\n");

    double **vectorMatrix = createVectorMatrix(dimension, numberOfVectors);
    fillVectorMatrix(dimension, numberOfVectors, vectorMatrix); 
    
    double **gramSchmidtVecMat = createVectorMatrix(dimension, numberOfVectors);
    double **gramSchmidtUnitVecMat = createVectorMatrix(dimension, numberOfVectors);

    gramSchmidt(vectorMatrix, gramSchmidtVecMat, gramSchmidtUnitVecMat, dimension, numberOfVectors);
    
    printf("Set of Orthogonalized Vectors:");
    for (int row = 0; row < numberOfVectors; row++){
        printf("\nVector %d: ", row + 1);
        for (int col = 0; col < dimension; col++){
            printf("%lf ", gramSchmidtVecMat[row][col]);
        }
    }

    printf("\n\nSet of Orthonormal Vectors:");
    for (int row = 0; row < numberOfVectors; row++){
        printf("\nVector %d: ", row + 1);
        for (int col = 0; col < dimension; col++){
            printf("%lf ", gramSchmidtUnitVecMat[row][col]);
        }
    }

    return 0;
}
