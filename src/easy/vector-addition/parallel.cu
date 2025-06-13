#include <iostream>
#include <vector>

__global__ void vector_addition(float *A, float *B, float *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    srand(time(0));

    int N = 100000000;

    size_t size = sizeof(float) * N;

    std::vector<float> a(N);
    std::vector<float> b(N);
    std::vector<float> c(N);

    for (int i = 0; i < N; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }

    float *d_a, *d_b, *d_c;

    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, a.data(), size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b.data(), size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int numberOfBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;

    std::cout << "-> Running with " << numberOfBlocks << " blocks!"
              << std::endl;
    std::cout << "-> Running with " << threadsPerBlock << " threads per block!"
              << std::endl;

    cudaEvent_t start, end;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    float elapsed = 0.0f;

    cudaEventRecord(start, 0);

    vector_addition<<<numberOfBlocks, threadsPerBlock>>>(d_a, d_b, d_c, N);

    cudaEventRecord(end, 0);

    cudaEventSynchronize(end);
    cudaEventElapsedTime(&elapsed, start, end);

    cudaEventDestroy(start);
    cudaEventDestroy(end);

    std::cout << "-> Elapsed: " << elapsed << " ms" << std::endl;

    cudaMemcpy(c.data(), d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    std::cout << "==========" << std::endl;
    std::cout << "Searching for differences..." << std::endl;

    float check, difference;
    for (int i = 0; i < N; i++) {
        check = a[i] + b[i];
        difference = abs(c[i] - check);
        if (difference > 0.0f) {
            std::cout << "-> Found difference!" << std::endl;
        }
    }

    return 0;
}