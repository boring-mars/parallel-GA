#include <iostream>
#include "runner/SerialRunner.h"
#include "runner/OpenMPRunner.h"

int main() {
//    SerialRunner runner;
    OpenMPRunner runner;

    auto start = std::chrono::high_resolution_clock::now();
    runner.run();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Running time: " << duration.count() << " ms" << std::endl;
    return 0;
}