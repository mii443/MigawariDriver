#include "ServerTrackedDeviceProvider.hpp"

vr::EVRInitError ServerTrackedDeviceProvider::Init(vr::IVRDriverContext *pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);

    std::string message = "Migawari driver initialized!\n";
    vr::VRDriverLog()->Log(message.c_str());

    return vr::VRInitError_None;
}

void ServerTrackedDeviceProvider::Cleanup() {
    VR_CLEANUP_SERVER_DRIVER_CONTEXT();
}

const char * const *ServerTrackedDeviceProvider::GetInterfaceVersions() {
    return vr::k_InterfaceVersions;
}
