#include <chrono>

int64_t getElapsedTime(std::chrono::time_point<std::chrono::system_clock,
                                               std::chrono::duration<double>>
                           start,
                       std::chrono::time_point<std::chrono::system_clock,
                                               std::chrono::duration<double>>
                           end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();
}