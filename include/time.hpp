#include <chrono>
#include <sycl/sycl.hpp>

int64_t getElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock,
                                               std::chrono::duration<double>>
                           start,
                       std::chrono::time_point<std::chrono::high_resolution_clock,
                                               std::chrono::duration<double>>
                           end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();
}

double syclElapsedTime(sycl::event event) {
    uint64_t start =
        event.get_profiling_info<sycl::info::event_profiling::command_start>();
    uint64_t end =
        event.get_profiling_info<sycl::info::event_profiling::command_end>();
    return (end - start) / 1e6;
}