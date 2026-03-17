#include <chrono>
#include <cmath>
#include <iostream>
#include <time.hpp>
#include <utils.hpp>
#include <vector>

int main() {
    const unsigned int N = 100000000;

    std::vector<float> a(N);

    for (unsigned int i = 0; i < N; i++) {
        a[i] = myRand();
    }
    a[0] = -1.f;  // Make sure at least one element is negative to fail if code
                  // is wrong

    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < N; i++) {
        a[i] = fmax(0, a[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "-> Duration: " << getElapsedTime(start, end) << " ms"
              << std::endl;

    bool success = true;
    for (unsigned int i = 0; i < N; i++) {
        if (a[i] < .0f) success = false;
    }

    std::cout << (success ? "Success" : "Failed") << std::endl;

    return 0;
}