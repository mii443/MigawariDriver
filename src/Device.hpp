#pragma once

#include "openvr_driver.h"

struct SharedDevice {
    vr::DriverPose_t actual_pose;
    
    bool overwrite = false;
    vr::DriverPose_t overwrite_pose;
};
