#include "ServerTrackedDeviceProvider.hpp"
#include "Device.hpp"
#ifdef _MSC_VER
#include <Windows.h>
#endif

vr::EVRInitError ServerTrackedDeviceProvider::Init(vr::IVRDriverContext *pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);

#ifdef _MSC_VER
    auto name = "MigawariDriver_k_unMaxTrackedDeviceCount";
    auto size = 4;
    HANDLE hSharedMemory = CreateFileMapping(NULL, NULL, PAGE_READWRITE, NULL, size, name);
    auto pMemory = (uint32_t*)MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, NULL, NULL, size);

    *pMemory = vr::k_unMaxTrackedDeviceCount;

    std::string message = "Initializing migawari driver...\n";
    vr::VRDriverLog()->Log(message.c_str());

    for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
        HANDLE pHandle = CreateFileMapping(NULL, NULL, PAGE_READWRITE, NULL, sizeof(SharedDevice), ("MigawariDriver_Device" + std::to_string(i)).c_str());
        devices[i] = (SharedDevice*)MapViewOfFile(pHandle, FILE_MAP_ALL_ACCESS, NULL, NULL, sizeof(SharedDevice));
    }
#endif

    return vr::VRInitError_None;
}

void ServerTrackedDeviceProvider::Cleanup() {
    VR_CLEANUP_SERVER_DRIVER_CONTEXT();
}

const char * const *ServerTrackedDeviceProvider::GetInterfaceVersions() {
    return vr::k_InterfaceVersions;
}
