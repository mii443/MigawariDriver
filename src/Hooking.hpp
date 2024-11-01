// Refer to https://github.com/pushrax/OpenVR-SpaceCalibrator/blob/master/OpenVR-SpaceCalibratorDriver/Hooking.h

#pragma once

#include <MinHook.h>
#include <map>
#include <string>

class IHook {
public:
    const std::string name;

    IHook(const std::string &name) : name(name) { }
    virtual ~IHook() { }

    virtual void Destroy() = 0;

    static bool Exists(const std::string &name);
    static void Register(IHook *hook);
    static void Unregister(IHook *hook);
    static void DestroyAll();

private:
    static std::map<std::string, IHook *> hooks;
};

template<class FuncType> class Hook : public IHook {
public:
    FuncType originalFunc = nullptr;
    Hook(const std::string &name) : IHook(name) { }

    bool CreateHookInObjectVTable(void *object, int vtableOffset, void *detourFunction) {
        void **vtable = *((void ***)object);

        targetFunc = vtable[vtableOffset];

        auto err = MH_CreateHook(targetFunc, detourFunction, (LPVOID *)&originalFunc);

        if (err != MH_OK) {
            vr::VRDriverLog()->Log("Failed to create hook.".c_str());
            return false;
        }

        err = MH_EnableHook(targetFunc);
        if (err != MH_OK) {
            vr::VRDriverLog()->Log("Failed to enable hook.".c_str());
            MH_RemoveHook(targetFunc);
            return false;
        }

        vr::VRDriverLog()->Log("Hook enabled.".c_str());
        enabled = true;
        return true;
    }

    void Destroy() {
        if (enabled) {
            MH_RemoveHook(targetFunc);
            enabled = false;
        }
    }

private:
    bool enabled = false;
    void* targetFunc = nullptr;
};
