
#include <stdio.h>




__global__ void use_local_memory_GPU(float in)
{
    float f;   
    f = in;     
}



__global__ void use_global_memory_GPU(float *array)
{
  
    array[threadIdx.x] = 2.0f * (float) threadIdx.x;
}




__global__ void use_shared_memory_GPU(float *array)
{
    
    int i, index = threadIdx.x;
    float average, sum = 0.0f;

 
    __shared__ float sh_arr[10];

    
    sh_arr[index] = array[index];

    __syncthreads();   
    for (i=0; i<index; i++) { sum += sh_arr[i]; }
    average = sum / (index + 1.0f);

        printf("Thread id = %d\t Average = %f\n",index,average);
    
    if (array[index] > average) { array[index] = average; }

   
    sh_arr[index] = 3.14;
}

int main(int argc, char **argv)
{
  
    use_local_memory_GPU<<<1, 10>>>(2.0f);

   
    float h_arr[10];   
float *d_arr;       

    cudaMalloc((void **) &d_arr, sizeof(float) * 10);
    
    cudaMemcpy((void *)d_arr, (void *)h_arr, sizeof(float) * 10, cudaMemcpyHostToDevice);
    
    use_global_memory_GPU<<<1, 10>>>(d_arr);  
   
    cudaMemcpy((void *)h_arr, (void *)d_arr, sizeof(float) * 10, cudaMemcpyDeviceToHost);
   

  
    use_shared_memory_GPU<<<1, 10>>>(d_arr);
    
    cudaMemcpy((void *)h_arr, (void *)d_arr, sizeof(float) * 10, cudaMemcpyHostToDevice);
  


    cudaDeviceSynchronize();
    return 0;
}
