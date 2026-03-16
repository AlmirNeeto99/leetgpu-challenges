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

    std::vector<float> a(N, 1.0f);
    std::vector<float> b(N, 2.0f);
    std::vector<float> c(N, .0f);

    {
        range<1> r(N);
        buffer<float> a_buf(a.data(), r);
        buffer<float> b_buf(b.data(), r);
        buffer<float> c_buf(c.data(), r);

        event event = q.submit([&](handler& h) {
            accessor a_acc = a_buf.get_access<access_mode::read>(h);
            accessor b_acc = b_buf.get_access<access_mode::read>(h);
            accessor c_acc = c_buf.get_access<access_mode::write>(h);

            h.parallel_for(r, [=](id<1> i) { c_acc[i] = a_acc[i] + b_acc[i]; });
        });
        event.wait();

        std::cout << "-> Duration: " << syclElapsedTime(event) << " ms"
                  << std::endl;
    }

    bool success = true;
    for (int i = 0; i < N; i++) {
        if (c[i] != 3.0f) {
            success = false;
            break;
        }
    }

    std::cout << (success ? "Success!" : "Verification Failed.") << "\n";

    return 0;
}