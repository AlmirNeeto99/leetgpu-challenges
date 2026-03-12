#include <iostream>
#include <string>
#include <sycl/sycl.hpp>
#include <utils.hpp>

using namespace sycl;

int main() {
    queue q;
    device device = q.get_device();
    printDeviceInfo(device);

    const unsigned int N = 4096;

    float* a = malloc_shared<float>(N, q);
    float* b = malloc_shared<float>(N, q);
    float* c = malloc_shared<float>(N, q);

    for (int i = 0; i < N; i++) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(i * 2);
    }

    q.parallel_for(range<1>(N), [=](id<1> i) { c[i] = a[i] + b[i]; }).wait();

    bool success = true;
    for (int i = 0; i < N; i++) {
        if (c[i] != i + (i * 2)) {
            success = false;
            break;
        }
    }

    std::cout << (success ? "Success!" : "Verification Failed.") << "\n";

    free(a, q);
    free(b, q);
    free(c, q);

    return 0;
}