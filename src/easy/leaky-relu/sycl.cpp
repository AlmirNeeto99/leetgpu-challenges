#include <iostream>
#include <string>
#include <sycl/sycl.hpp>
#include <time.hpp>
#include <utils.hpp>
#include <vector>

using namespace sycl;

int main() {
    queue q(default_selector_v, {property::queue::enable_profiling()});
    device device = q.get_device();
    printDeviceInfo(device);

    const unsigned int N = 100000000;
    const float alpha = 0.01;
    std::vector<float> a(N), b(N);

    for (unsigned int i = 0; i < N; i++) {
        a[i] = myRand();
        b[i] = myRand();
    }

    {
        range<1> r(N);
        buffer<float> b_a(a.data(), r), b_b(b.data(), r);

        event event = q.submit([&](handler& h) {
            accessor acc_a = b_a.get_access<access_mode::read>(h);
            accessor acc_b = b_b.get_access<access_mode::write>(h);
            h.parallel_for(r, [=](id<1> i) {
                if (acc_a[i] <= .0f) {
                    acc_b[i] = alpha * acc_a[i];
                }
            });
        });
        event.wait();

        std::cout << "-> Duration: " << syclElapsedTime(event) << " ms"
                  << std::endl;
    }

    bool success = true;
    for (unsigned int i = 0; i < N; i++) {
        if (a[i] <= .0f && alpha * a[i] != b[i]) {
            success = false;
            break;
        }
    }
    std::cout << (success ? "Success!" : "Verification Failed.") << "\n";

    return 0;
}