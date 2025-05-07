#pragma once

namespace steamvr_bridge {

struct Pose {
    float position[3];
    float orientation[4]; // Quaternion
};

void init();
void update_pose(const Pose& pose);
void shutdown();

}
