#include <openvr.h>

int main() {
    if (!vr::VR_IsHmdPresent()) {
        fprintf(stderr, "No HMD detected.\n");
        return -1;
    }

    vr::IVRSystem* vr_system = vr::VR_Init(nullptr, vr::VRApplication_Scene);
    if (!vr_system) {
        fprintf(stderr, "Failed to initialize OpenVR.\n");
        return -1;
    }

    // Placeholder: SLAM pose would go here
    vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
    vr_system->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, poses, vr::k_unMaxTrackedDeviceCount);

    // clean up
    vr::VR_Shutdown();
    return 0;
}
