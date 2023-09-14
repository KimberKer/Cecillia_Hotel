
#include "Physics.h"
#include <thread> // for sleep_for

void PhysicsSystemSimulation() {
    // This is a dummy physics system that simulates some workload
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
