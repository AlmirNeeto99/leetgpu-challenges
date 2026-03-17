#include <iostream>
#include <string>
#include <sycl/sycl.hpp>
#include <time.hpp>
#include <utils.hpp>
#include <vector>

using namespace sycl;

int main() {
    srand(99);
    queue q(default_selector_v, {property::queue::enable_profiling()});
    device device = q.get_device();
    printDeviceInfo(device);

    const unsigned int N = 100000000;

    std::vector<float> a(N);

    for (unsigned int i = 0; i < N; i++) {
        a[i] = myRand();
    }
    a[0] = -1.f;  // Make sure at least one element is negative to fail if code
                  // is wrong

    {
        range<1> r(N);
        buffer<float> b_a(a.data(), r);

        event event = q.submit([&](handler& h) {
            accessor a_acc = b_a.get_access<access_mode::read_write>(h);
            h.parallel_for(r, [=](id<1> i) { a_acc[i] = fmax(0, a_acc[i]); });
        });
        event.wait();

        std::cout << "-> Duration: " << syclElapsedTime(event) << " ms"
                  << std::endl;
    }

    bool success = true;
    for (unsigned int i = 0; i < N; i++) {
        if (a[i] < .0f) success = false;
    }

    std::cout << (success ? "Success!" : "Verification Failed.") << "\n";

    return 0;
}