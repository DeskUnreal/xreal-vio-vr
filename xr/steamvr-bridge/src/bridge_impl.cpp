#include "steamvr_bridge/bridge.h"
#include <iostream>

namespace steamvr_bridge {

void init() {
    std::cout << "[SteamVR Bridge] Init called" << std::endl;
}

void update_pose(const Pose& pose) {
    std::cout << "[SteamVR Bridge] Pose: "
              << "Pos(" << pose.position[0] << ", "
                       << pose.position[1] << ", "
                       << pose.position[2] << ") "
              << "Quat(" << pose.orientation[0] << ", ... )" << std::endl;
}

void shutdown() {
    std::cout << "[SteamVR Bridge] Shutdown called" << std::endl;
}

}
