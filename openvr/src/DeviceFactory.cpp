#include <memory>
#include <string.h>
#include <openvr_driver.h>

#include "Driver.hpp"

static std::shared_ptr<XRealAir2UltraDriver::VRDriver> driver;

VR_INTERFACE
void *HmdDriverFactory( const char *pInterfaceName, int *pReturnCode )
{
	if (strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName)) {
		if (pReturnCode)
			*pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
		return NULL;
	}

	driver = std::make_shared<XRealAir2UltraDriver::VRDriver>();
	return driver.get();
}
