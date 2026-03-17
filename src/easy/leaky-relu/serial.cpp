#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <time.hpp>
#include <utils.hpp>
#include <vector>

void leaky_relu(const std::vector<float> a, std::vector<float>& b,
                const float alpha, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        if (a[i] <= .0f) {
            b[i] = alpha * a[i];
        }
    }
}

int main() {
    srand(99);

    unsigned int N = 100000000;
    const float alpha = 0.01;

    std::vector<float> a(N), b(N);

    std::cout << "-> Randomizing A" << std::endl;

    for (unsigned int i = 0; i < N; i++) {
        a[i] = myRand();
    }
    a[0] = -1.f;

    std::cout << "-> Applying Leaky RELU over A" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    leaky_relu(a, b, alpha, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "-> Duration: " << getElapsedTime(start, end) << " ms"
              << std::endl;

    bool success = true;
    for (unsigned int i = 0; i < N; i++) {
        if (a[i] <= 0.f && a[i] * alpha != b[i]) {
            success = false;
        }
    }
    std::cout << (success ? "Success" : "Failed") << std::endl;

    return 0;
}