#include "ServerTrackedDeviceProvider.hpp"
#include "Device.hpp"
#include "InterfaceHookInjector.hpp"
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

    auto hMapFile = CreateFileMapping(NULL, NULL, PAGE_READWRITE, NULL, sizeof(SharedDevice) * 64, "MigawariDriver_Devices");
    devices = (SharedDevice*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, NULL, NULL, sizeof(SharedDevice) * 64);

    InjectHooks(this, pDriverContext);
#endif

    return vr::VRInitError_None;
}

void ServerTrackedDeviceProvider::Cleanup() {
    VR_CLEANUP_SERVER_DRIVER_CONTEXT();
}

void ServerTrackedDeviceProvider::SetSharedDevice(vr::DriverPose_t &newPose, uint32_t unWhichDevice) {
    devices[unWhichDevice].actual_pose = newPose;

    if (devices[unWhichDevice].overwrite) {
        auto overwrite_pose = devices[unWhichDevice].overwrite_pose;
        newPose.qRotation = overwrite_pose.qRotation;

        for (int i = 0; i < 3; i++) {
            newPose.vecAcceleration[i] = overwrite_pose.vecAcceleration[i];
            newPose.vecAngularAcceleration[i] = overwrite_pose.vecAngularAcceleration[i];
            newPose.vecPosition[i] = overwrite_pose.vecPosition[i];
            newPose.vecVelocity[i] = overwrite_pose.vecVelocity[i];
        }
    }
}

const char * const *ServerTrackedDeviceProvider::GetInterfaceVersions() {
    return vr::k_InterfaceVersions;
}
