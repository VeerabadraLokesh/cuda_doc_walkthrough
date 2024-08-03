#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265359 
#define N 16
#define MAX_ERR 1e-6

void vector_add(float **C, float **A, float **B) {
    for (int i = 0; i < N ; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main(){
    float **a, **b, **c;

    // Allocate host memory
    // a   = (float*)malloc(sizeof(float) * N);
    a = (float **)malloc(N * sizeof(float *));
    b = (float **)malloc(N * sizeof(float *));
    c = (float **)malloc(N * sizeof(float *));
    for (int i=0; i < N; i++) {
        a[i] = malloc(N * sizeof(float));
        b[i] = malloc(N * sizeof(float));
        c[i] = malloc(N * sizeof(float));
        for(int j = 0; j < N; j++){
            a[i][j] = 1.0f;
            b[i][j] = 2.0f;
        }
    }

    // Executing kernel 
    vector_add(c, a, b);

    // Verification
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            assert(fabs(c[i][j] - a[i][j] - b[i][j]) < MAX_ERR);
        }
    }

    printf("PASSED\n");

    // Deallocate host memory
    free(a); 
    free(b); 
    free(c);
}
