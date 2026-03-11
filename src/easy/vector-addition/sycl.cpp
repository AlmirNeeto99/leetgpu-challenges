#include <iostream>
#include <string>
#include <sycl/sycl.hpp>

using namespace sycl;

int main() {
    queue queue;

    device device = queue.get_device();
    std::string device_name = device.get_info<info::device::name>();
    platform platform = device.get_info<info::device::platform>();
    std::string platform_name = platform.get_info<info::platform::name>();

    if (device.has(sycl::aspect::gpu)) {
        std::cout << "Running on GPU: " << device_name << std::endl;
    } else if (device.has(sycl::aspect::cpu)) {
        std::cout << "Running on CPU: " << device_name << std::endl;
    } else {
        std::cout << "Running on an unknown device: " << device_name
                  << std::endl;
    }

    std::cout << "Platform: " << platform_name << std::endl;

    return 0;
}