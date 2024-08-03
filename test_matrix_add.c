#include <stdio.h>
#include <stdlib.h>

void addMatrices(float **matrix1, float **matrix2, float **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void printMatrix(float **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Dynamic allocation of matrices
    float **matrix1 = (float **)malloc(rows * sizeof(float *));
    float **matrix2 = (float **)malloc(rows * sizeof(float *));
    float **result = (float **)malloc(rows * sizeof(float *));
    
    for (int i = 0; i < rows; i++) {
        matrix1[i] = (float *)malloc(cols * sizeof(float));
        matrix2[i] = (float *)malloc(cols * sizeof(float));
        result[i] = (float *)malloc(cols * sizeof(float));
    }

    // Input elements for matrix1
    printf("Enter elements for matrix1:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%f", &matrix1[i][j]);
        }
    }

    // Input elements for matrix2
    printf("Enter elements for matrix2:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%f", &matrix2[i][j]);
        }
    }

    // Add matrices
    addMatrices(matrix1, matrix2, result, rows, cols);

    // Print matrices
    printf("Matrix 1:\n");
    printMatrix(matrix1, rows, cols);

    printf("Matrix 2:\n");
    printMatrix(matrix2, rows, cols);

    printf("Resultant Matrix:\n");
    printMatrix(result, rows, cols);

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
