#include <iostream>
#include "runner/SerialRunner.h"
#include "runner/OpenMPRunner.h"
#include "runner/SerialCellularRunner.h"
#include "runner/OpenMPCellularRunner.h"
#include "runner/MPIRunner.h"
#include "runner/MPICellularRunner.h"

/**
 * This is the entry point of the program
 */
int main() {
    // Choose the runner to use
//    SerialRunner runner;
//    SerialCellularRunner runner;
//    OpenMPRunner runner;
//    OpenMPCellularRunner runner;
//    MPIRunner runner;
    MPICellularRunner runner;

    // Run the genetic algorithm
    runner.run();

    // Show the running information and solutions found
    runner.show_running_info();
    runner.show_solutions();
    return 0;
}