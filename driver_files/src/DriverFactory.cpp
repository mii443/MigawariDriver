#include "DriverFactory.hpp"
#include "ServerTrackedDeviceProvider.hpp"
#include "VRWatchdogProvider.hpp"

static ServerTrackedDeviceProvider g_serverTrackedDeviceProvider;
static VRWatchdogProvider g_watchdogProvider;

void *HmdDriverFactory(const char* pInterfaceName, int* pReturnCode) {
    if (strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName) == 0) {
        return &g_serverTrackedDeviceProvider;
    }
    if (strcmp(vr::IVRWatchdogProvider_Version, pInterfaceName) == 0) {
        return &g_watchdogProvider;
    }

    if (pReturnCode)
        *pReturnCode = vr::VRInitError_Init_InterfaceNotFound;

    return nullptr;
}
