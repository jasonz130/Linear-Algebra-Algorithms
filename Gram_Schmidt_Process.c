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

void vectorScalarMultiplication(double **vectorMatrix, int dimension, int vectorToMultiply, double *vectorVariableName, int scalar){
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

void unitVector(double **vectorMatrix, int dimension, int vectorToUnitize, double *vectorVariableName){
    double magnitude = vectorMagnitude(vectorMatrix, dimension, vectorToUnitize);
    for (int col = 0; col < dimension; col++){
        vectorVariableName[col] = vectorMatrix[vectorToUnitize][col] / magnitude;
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

void gramSchmidt(double **vectorMatrix, int dimension, int numberofVectors){
    // COPY THE VECTOR MATRIX ALLOCATED MEMORY SIZE
    double **gramSchmidtVecMat = createVectorMatrix(dimension, numberofVectors);
    

    int counter = 0;
    for (int k = 1; k <= numberofVectors; k++){
        for (int col = 0; col < dimension; col++){
            gramSchmidtVecMat[k-1][col] = vectorMatrix[k-1][col];
        }

        if (k > 1){
            // ALLOCATE VECTOR VARIABLE FOR SCALAR MULTIPLICATION STEP
            double *allocateVecVarScalarMult = allocateVector(dimension);


            // ALLOCATE VECTOR VARIABLE FOR VECTORMATRIX;
            double *allocateVecVarVectorMatrix = allocateVector(dimension);
            // COPY 
            for (int column = 0; column < dimension; column++){
                allocateVecVarVectorMatrix[k-1][column] = vectorMatrix[k-1][column];
            }

            // ALLOCATE VECTOR ADDITION STEP
            double *openVar = allocateVector(dimension);
            // INIT OPENVAR ENTRIES TO 0
            for (int iteration = 0; iteration < dimension; iteration++){
                openVar[iteration] = 0;
            }


            for (int i = 1; i < k-1; i++){
                double iterativeVariable;

                double dotProduct = dotProd(vectorMatrix, gramSchmidtVecMat, dimension, k-1, i-1);
                double magnitudeSquared = vectorMagnitude(gramSchmidtVecMat, dimension, i-1) * vectorMagnitude(gramSchmidtVecMat, dimension, i-1);
                double division = dotProduct / magnitudeSquared;
                double scalarVectorMultiply = vectorScalarMultiplication(gramSchmidtVecMat, dimension, i-1, allocateVecVarScalarMult, division);

                vectorAddition(openVar, scalarVectorMultiply, dimension, openVar);
            }

            vectorSubtraction(vectorMatrix, vectorAddition, dimension, k-1, gramSchmidtVecMat, k-1);
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
    
    for (int i = 0; i < numberOfVectors; i++){
        printf("\n");
        for (int j = 0; j < dimension; j++){
            printf("%lf ", vectorMatrix[i][j]);
        }
    }

// // DOT PRODUCT
//     printf("\n");
//     printf("Dot product = %lf", dotProd(vectorMatrix, dimension, 0, 1));
    

// ADDITION/SUBTRACTION VECTOR
    printf("\n");
    printf("Subtracted vector = ");
    double *vector = allocateVector(dimension);
    vectorSubtraction(vectorMatrix, dimension, 1, 0, vector);
    for (int row = 0; row < dimension; row++){
        printf("%lf ", vector[row]);
    }

// SCALAR MULTIPLCATION
    printf("\n");
    printf("Scalar multiplication = ");
    double *vector2 = allocateVector(dimension);
    vectorScalarMultiplication(vectorMatrix, dimension, 0, vector2, 5);
    for (int row = 0; row < dimension; row++){
        printf("%lf ", vector2[row]);
    }

// VECTOR MAGNITUDE
    printf("\n");
    printf("Vector magnitude = %lf", vectorMagnitude(vectorMatrix, dimension, 0));

// UNIT VECTOR
    printf("\n");
    printf("Unit vector = ");
    double *vector3 = allocateVector(dimension);
    unitVector(vectorMatrix, dimension, 0, vector3);
    for (int row = 0; row < dimension; row++){
        printf("%lf ", vector3[row]);
    }


    return 0;
}