#include <stdio.h>
#include <stdlib.h>
#define N 10000000

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

__global__ void vector_add(float *out, float *a, float *b, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    out[tid] = a[tid] + b[tid];
}

int main(){
    float *a, *b, *out;
    float *d_a, *d_b, *d_out;

    a = (float*)malloc(sizeof(float) * N);
    b = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Allocate device memory for a
    gpuErrchk(cudaMalloc((void**)&d_a, sizeof(float) * N));
    gpuErrchk(cudaMalloc((void**)&d_b, sizeof(float) * N));
    gpuErrchk(cudaMalloc((void**)&d_out, sizeof(float) * N));

    // Transfer data from host to device memory
    gpuErrchk(cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice));
    gpuErrchk(cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice));

    int grid_blocks = N/256;

    vector_add<<<grid_blocks,256>>>(d_out, d_a, d_b, N);
    
    gpuErrchk(cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost));

    // Cleanup after kernel execution
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);
    free(a);
    free(b);
    free(out);

    return 0;
}

