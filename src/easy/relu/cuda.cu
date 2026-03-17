#include <cuda_runtime.h>

#include <iostream>
#include <utils.hpp>
#include <vector>

using namespace std;

__global__ void relu(const float* input, float* output, int n) {
    int i = threadIdx.x;
    if (i < n) {
        output[i] = max(0, input[i]);
    }
}

int main() {
    srand(99);

    int N = 100000000;

    size_t b = sizeof(float) * N;

    vector<float> input(N);
    vector<float> output(N);

    cout << "-> Randomizing input" << endl;

    for (int i = 0; i < N; i++) {
        input[i] = myRand();
        output[i] = myRand();
    }
    output[0] = -1.f;  // Make sure one element is negative

    float *d_input, d_output;  // Device pointer

    cudaMalloc(&d_input, b);
    cudaMalloc(&d_output, b);

    cudaMemCpy(d_input, input.data(), b, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int numberOfBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;

    cout << "-> Running with " << numberOfBlocks << " blocks!" << endl;
    cout << "-> Running with " << threadsPerBlock << " threads per block!"
         << endl;

    cudaEvent_t start, end;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    float elapsed = 0.0f;

    cudaEventRecord(start, 0);

    relu<<<numberOfBlocks, threadsPerBlock>>>(d_input, d_output, N);

    cudaEventRecord(end, 0);

    cudaEventSynchronize(end);
    cudaEventElapsedTime(&elapsed, start, end);

    cudaEventDestroy(start);
    cudaEventDestroy(end);

    cout << "-> Elapsed: " << elapsed << " ms" << endl;

    cudaMemCpy(output.data(), d_output, b, cudaMemcpyDeviceToHost);
    cudaFree(d_input);
    cudaFree(d_output);

    bool hasNegative = false;
    for (int i = 0; i < N; i++) {
        if (output[i] < .0f) {
            hasNegative = true;
            break
        }
    }

    cout << (hasNegative ? 'Failed' : 'Success') << endl;

    return 0;
}