#include <iostream>
#include "runner/SerialRunner.h"
#include "runner/OpenMPRunner.h"
#include "runner/SerialCellularRunner.h"
#include "runner/OpenMPCellularRunner.h"
#include "runner/MPIRunner.h"
#include "runner/MPICellularRunner.h"

int main() {
//    SerialRunner runner;
//    SerialCellularRunner runner;
//    OpenMPRunner runner;
//    OpenMPCellularRunner runner;
//    MPIRunner runner;
    MPICellularRunner runner;

    runner.run();
    runner.show_running_info();
//    runner.show_solutions();
    return 0;
}