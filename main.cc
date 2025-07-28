#include <iostream>
#include "runner/SerialRunner.h"
#include "runner/OpenMPRunner.h"
#include "runner/SerialCellularRunner.h"
#include "runner/OpenMPCellularRunner.h"

int main() {
//    SerialRunner runner;
//    SerialCellularRunner runner;
//    OpenMPRunner runner;
    OpenMPCellularRunner runner;

    runner.run();
    runner.show_running_info();
//    runner.show_solutions();
    return 0;
}