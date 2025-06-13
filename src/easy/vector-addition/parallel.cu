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

    int N = 50000000;

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
    int numberOfBlocks = (N / threadsPerBlock) + 1;

    std::cout << "-> Running with " << numberOfBlocks << " blocks!"
              << std::endl;
    std::cout << "-> Running with " << threadsPerBlock << " threads per block!"
              << std::endl;

    cudaEvent_t start, end;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    float elapsed = 0.0f;

    vector_addition<<<numberOfBlocks, threadsPerBlock>>>(d_a, d_b, d_c, N);
    cudaEventElapsedTime(&elapsed, start, end);

    std::cout << "-> Elapsed: " << elapsed << std::endl;

    cudaMemcpy(c.data(), d_c, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    std::cout << "==========" << std::endl;

    for (int i = 0; i < 10; i++) {
        std::cout << "-> Result: " << c[i] << std::endl;
    }

    return 0;
}