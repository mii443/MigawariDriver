#pragma once

#include <openvr_driver.h>

extern "C"
#ifdef _MSC_VER
  __declspec(dllexport) 
#endif
  void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode);
