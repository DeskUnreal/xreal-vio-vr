#include "HMDDevice.hpp"

using namespace XRealAir2UltraDriver;

HMDDevice::HMDDevice(vr::IVRDriverContext* pDriverContext) : last_pose()
{
        driver_host = vr::VRServerDriverHost();
}

HMDDevice::~HMDDevice()
{
}

void HMDDevice::RunFrame()
{
        // Setup pose for this frame
        last_pose.qRotation.w = 1.0;
        last_pose.qRotation.x = 0.0;
        last_pose.qRotation.y = 0.0;
        last_pose.qRotation.z = 0.0;

        last_pose.vecPosition[0] = 0.0;
        last_pose.vecPosition[1] = 0.0;
        last_pose.vecPosition[2] = 0.0;

        driver_host->TrackedDevicePoseUpdated(deviceId, last_pose, sizeof(last_pose));
}

/* ITrackedDeviceServerDriver */
vr::EVRInitError HMDDevice::Activate(uint32_t unObjectId)
{
        deviceId = unObjectId;

        return vr::EVRInitError::VRInitError_None;
}

void HMDDevice::Deactivate()
{
}

void HMDDevice::EnterStandby()
{
}

void* HMDDevice::GetComponent(const char* pchComponentNameAndVersion)
{
        return NULL;
}

void HMDDevice::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
}

vr::DriverPose_t HMDDevice::GetPose()
{
        return last_pose;
}


/* IVRDisplayComponent */
void HMDDevice::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnX = 0;
    *pnY = 0;
    *pnWidth = 2 * 1920;
    *pnHeight = 1080;
}

bool HMDDevice::IsDisplayOnDesktop()
{
        return true;
}

bool HMDDevice::IsDisplayRealDisplay()
{
    return false;
}

void HMDDevice::GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight)
{
        *pnWidth = 2 * 1920;
        *pnHeight = 1080;
}

void HMDDevice::GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnY = 0;
    *pnWidth = 1920;
    *pnHeight = 1080;

    if (eEye == vr::EVREye::Eye_Left) {
        *pnX = 0;
    } else {
        *pnX = 1920;
    }
}

void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
    *pfLeft = -1;
    *pfRight = 1;
    *pfTop = -1;
    *pfBottom = 1;
}

vr::DistortionCoordinates_t HMDDevice::ComputeDistortion(vr::EVREye eEye, float fU, float fV)
{
    vr::DistortionCoordinates_t coordinates;

    coordinates.rfBlue[0] = fU;
    coordinates.rfBlue[1] = fV;
    coordinates.rfGreen[0] = fU;
    coordinates.rfGreen[1] = fV;
    coordinates.rfRed[0] = fU;
    coordinates.rfRed[1] = fV;

    return coordinates;
}
