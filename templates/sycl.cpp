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

    {
        range<1> r(N);

        event event =
            q.submit([&](handler& h) { h.parallel_for(r, [=](id<1> i) {}); });
        event.wait();

        std::cout << "-> Duration: " << syclElapsedTime(event) << " ms"
                  << std::endl;
    }

    bool success = true;

    std::cout << (success ? "Success!" : "Verification Failed.") << "\n";

    return 0;
}