#include <iostream>
#include <string>
#include <sycl/sycl.hpp>
#include <utils.hpp>

using namespace sycl;

int main() {
    queue queue;
    device device = queue.get_device();
    printDeviceInfo(device);

    return 0;
}