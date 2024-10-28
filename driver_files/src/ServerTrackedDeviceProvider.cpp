#include "ServerTrackedDeviceProvider.hpp"
#include <Windows.h>

vr::EVRInitError ServerTrackedDeviceProvider::Init(vr::IVRDriverContext *pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);

    auto name = "MigawariDriver";
    auto size = 4;
    HANDLE hSharedMemory = CreateFileMapping(NULL, NULL, PAGE_READWRITE, NULL, size, name);
    pMemory = (int*)MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, NULL, NULL, size);

    *pMemory = 100;

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
