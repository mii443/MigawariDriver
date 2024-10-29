#pragma once

#include "Device.hpp"

#include <openvr_driver.h>

class ServerTrackedDeviceProvider : public vr::IServerTrackedDeviceProvider {
public:
    virtual vr::EVRInitError Init(vr::IVRDriverContext *pDriverContext) override;
    virtual void Cleanup() override;
    virtual const char * const *GetInterfaceVersions() override;
    virtual void RunFrame() { };
	virtual bool ShouldBlockStandbyMode() { return false; };
	virtual void EnterStandby() { };
	virtual void LeaveStandby() { };
private:
    SharedDevice* devices[vr::k_unMaxTrackedDeviceCount];
};
