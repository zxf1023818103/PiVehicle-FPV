#include "pifpv.h"
#include <glog/logging.h>
#include <glob.h>
#include <string>

namespace PiVehicle {
    int QueryFpvCamera(FpvCameraList &list) {
        LOG(INFO) << "Querying camera...";
        glob_t *handle = nullptr;
        glob("/dev/video[0-9]", GLOB_NOSORT, nullptr, handle);
        if (handle->gl_pathc != 0)
            LOG(INFO) << handle->gl_pathc << " camera(s) found:";
        else {
            LOG(WARNING) << "No camera found in /dev.";
            return 1;
        }
        for (int i = 0; i < handle->gl_pathc; ++i) {
            list.emplace_back(static_cast<const char *>(handle->gl_pathv[i]));
            LOG(INFO) << "\t\t" << handle->gl_pathv[i];
        }
        globfree(handle);
        return 0;
    }
};  // namespace PiVehicle