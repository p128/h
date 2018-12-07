#include <stdio.h>
#include <stdlib.h>
#include <math.h>


__global__ void vecAdd(double *a, double *b, double *c, int n)
{
    
    int id = blockIdx.x*blockDim.x+threadIdx.x;

 
    if (id < n)
        c[id] = a[id] + b[id];
}

int main( int argc, char* argv[] )
{
    
    int n = 10;

    
    double *h_a;
    double *h_b;
    
    double *h_c;

    
    double *d_a;
    double *d_b;
    
    double *d_c;

    size_t bytes = n*sizeof(double);

  
    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);
   
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);

    int i;
  
    for( i = 0; i < n; i++ ) {
        h_a[i] = i;
        h_b[i] = i;
    }

 
    cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);

    int blockSize, gridSize;

    
    blockSize = 100;

   
    gridSize = (int)ceil((float)n/blockSize);

    
    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    
    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );

  
    double sum = 0;
    for(i=0; i<n; i++)
        printf(" %f + %f =%f\n",h_a[i],h_b[i],h_c[i]);
 

 cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

  
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
