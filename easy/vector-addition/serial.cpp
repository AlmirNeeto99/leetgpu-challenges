#include <chrono>
#include <iomanip>
#include <iostream>
#include <time.hpp>
#include <vector>

void vector_addition(std::vector<float> a, std::vector<float> b,
                     std::vector<float> c, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    srand(time(0));

    unsigned int N = 100000000;

    std::vector<float> a(N);
    std::vector<float> b(N);
    std::vector<float> c(N);

    std::cout << "-> Randomization A and B" << std::endl;

    for (unsigned int i = 0; i < N; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }

    std::cout << "-> Adding vectors A and B into C" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    vector_addition(a, b, c, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "-> Vectors A and B added into C" << std::endl;

    std::cout << "-> Duration: " << getElapsedTime(start, end) << " ms"
              << std::endl;

    return 0;
}