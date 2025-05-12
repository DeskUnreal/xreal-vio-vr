#include "Driver.hpp"

using namespace XRealAir2UltraDriver;

vr::EVRInitError VRDriver::Init(vr::IVRDriverContext *pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);

	Log("Activating ...");

	hmd_device = new HMDDevice(pDriverContext);
	if (!vr::VRServerDriverHost()->TrackedDeviceAdded(
		    "serial", vr::TrackedDeviceClass_HMD, hmd_device))
		return vr::VRInitError_Driver_HmdDisplayNotFound;

	Log("Registered HMDDevice ...");

	return vr::VRInitError_None;
}

const char *const *VRDriver::GetInterfaceVersions()
{
	return vr::k_InterfaceVersions;
}

void VRDriver::Cleanup()
{
	delete hmd_device;

	VR_CLEANUP_SERVER_DRIVER_CONTEXT();
}

void VRDriver::RunFrame()
{
	hmd_device->RunFrame();
}

bool VRDriver::ShouldBlockStandbyMode()
{
	return false;
}

void VRDriver::EnterStandby()
{
}

void VRDriver::LeaveStandby()
{
}
