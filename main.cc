#include <iostream>
#include "runner/SerialRunner.h"
#include "runner/OpenMPRunner.h"

int main() {
    SerialRunner runner;
//    OpenMPRunner runner;

    runner.run();
    runner.show_running_info();
//    runner.show_solutions();
    return 0;
}