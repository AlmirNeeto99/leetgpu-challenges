#include <iostream>
#include <string>
#include <sycl/sycl.hpp>

using namespace sycl;

void printDeviceInfo(device device) {
    std::string device_name = device.get_info<info::device::name>();

    platform platform = device.get_info<info::device::platform>();
    std::cout << "-> Platform: " << platform.get_info<info::platform::name>()
              << std::endl;

    if (device.has(sycl::aspect::gpu)) {
        std::cout << "-> Running on GPU: " << device_name << std::endl;
    } else if (device.has(sycl::aspect::cpu)) {
        std::cout << "-> Running on CPU: " << device_name << std::endl;
    } else {
        std::cout << "-> Running on an unknown device: " << device_name
                  << std::endl;
    }
}

float myRand() {
    size_t max = RAND_MAX;
    size_t half = (size_t)max / 2;
    return (float)((rand() - half) / max);
}