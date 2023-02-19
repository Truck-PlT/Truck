%%cu
#include <cstdio>
#include <iostream>



__global__ void sendData(){
    printf("Send Velocity and Direction \n");
}

int main() {
    
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);


    cudaEventRecord(start);

    sendData<<<1,1>>>(); 

    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    float time = 0;
    cudaEventElapsedTime(&time, start, stop); 

    printf("The time required : ");
	  std::cout<<time;
    
    return 0;
}
