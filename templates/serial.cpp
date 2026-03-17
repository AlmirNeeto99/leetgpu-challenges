#include <chrono>
#include <iomanip>
#include <iostream>
#include <time.hpp>
#include <utils.hpp>
#include <vector>

void kernel(std::vector<float> a, std::vector<float> b, std::vector<float> c,
            unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
    }
}

int main() {
    srand(99);

    unsigned int N = 100000000;

    std::vector<float> a(N), b(N), c(N);

    std::cout << "-> Randomizing A and B" << std::endl;

    for (unsigned int i = 0; i < N; i++) {
        a[i] = myRand();
        b[i] = myRand();
    }

    std::cout << "-> Executing kernel for vector A, B and C" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    kernel(a, b, c, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "-> Done!" << std::endl;

    std::cout << "-> Duration: " << getElapsedTime(start, end) << " ms"
              << std::endl;

    return 0;
}