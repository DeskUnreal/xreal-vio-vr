#pragma once

#include <openvr_driver.h>
#include "HMDDevice.hpp"

namespace XRealAir2UltraDriver {
    class VRDriver : public vr::IServerTrackedDeviceProvider {
    public:
        // Inherited via IServerTrackedDeviceProvider
        virtual vr::EVRInitError Init(vr::IVRDriverContext* pDriverContext) override;
        virtual void Cleanup() override;
	virtual const char * const *GetInterfaceVersions() override;
        virtual void RunFrame() override;
        virtual bool ShouldBlockStandbyMode() override;
        virtual void EnterStandby() override;
        virtual void LeaveStandby() override;
        virtual ~VRDriver() = default;

        void Log(std::string message) {
            std::string message_endl = message + "\n";
                vr::VRDriverLog()->Log(message_endl.c_str());
        };

    private:
        HMDDevice *hmd_device;
    };
};
