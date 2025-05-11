#include <string.h>
#include "HMDDevice.hpp"

using namespace XRealAir2UltraDriver;

HMDDevice::HMDDevice(vr::IVRDriverContext* pDriverContext) : last_pose()
{
        driver_host = vr::VRServerDriverHost();

        /* TODO: Initialize device, get callibration data, etc. */
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

        /* TODO:
         * - Turn on FullHD SBS mode
         * - enable IMU
         * - start helper thread for USB traffic?
         */

        return vr::EVRInitError::VRInitError_None;
}

void HMDDevice::Deactivate()
{
        /* TODO: Switch back to normal display mode, disable IMU? */
}

void HMDDevice::EnterStandby()
{
        /* TODO: Disable IMU reporting? What about leaving standby? */
}

void* HMDDevice::GetComponent(const char* pchComponentNameAndVersion)
{
        /* This class/instance is implementing IVRDisplayComponent */
        if (!strcmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
                return this;

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
        /* TODO: Is it true that we are a real display? */
        return true;
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

void HMDDevice::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
    *pfLeft = -1;
    *pfRight = 1;
    *pfTop = -1;
    *pfBottom = 1;
}

/* TODO: We do not have color aberration, however the hardware does provide a
 * distortion table for all pixels.
 * We should use the per-eye hardware provided table here.
 */
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

bool HMDDevice::ComputeInverseDistortion(vr::HmdVector2_t *pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV )
{
    vr::DistortionCoordinates_t coordinates;

    pResult->v[0] = fU;
    pResult->v[1] = fV;

    return true;
}
