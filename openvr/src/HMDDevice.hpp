#pragma once

#include <openvr_driver.h>

namespace XRealAir2UltraDriver {
    class HMDDevice : public vr::IVRDisplayComponent, public vr::ITrackedDeviceServerDriver {
        public:
            HMDDevice(vr::IVRDriverContext* pDriverContext);
            ~HMDDevice();

            void RunFrame();

            // Inherited via ITrackedDeviceServerDriver
            virtual vr::EVRInitError Activate(uint32_t unObjectId) override;
            virtual void Deactivate() override;
            virtual void EnterStandby() override;
            virtual void* GetComponent(const char* pchComponentNameAndVersion) override;
            virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
            virtual vr::DriverPose_t GetPose() override;

            // Inherited via IVRDisplayComponent
            virtual void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
            virtual bool IsDisplayOnDesktop() override;
            virtual bool IsDisplayRealDisplay() override;
            virtual void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
            virtual void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
            virtual void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
            virtual vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;
            virtual bool ComputeInverseDistortion(vr::HmdVector2_t *pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV ) override;

    private:
        vr::IVRServerDriverHost* driver_host;

        uint32_t deviceId;

        vr::DriverPose_t last_pose;
    };
};