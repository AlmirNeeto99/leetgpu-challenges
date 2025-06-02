#include <cuda_runtime.h>

#include <iostream>

using namespace std;

__global__ void myKernel(global int *a, global int *b, global int *c, int n) {
    int i = threadIdx.x;
    if (i < n) {
    }
}

int main() {
    cout << "Hello from CUDA (from CPU)" << endl;

    return 0;
}