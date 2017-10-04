#include "pifpv.h"
#include <glog/logging.h>
#include <stdlib.h>
#include <glob.h>
#include <errno.h>

namespace PiVehicle {
    bool isInit = false;
    glob_t handle;
    int QueryFpvCamera(FpvCameraList *list) {
        LOG(INFO) << "Querying camera...";
        if (!list) {
            // TODO: Log error of null pointer.
            errno = EINVAL;
            return 1;
        }
        glob("/dev/video[0-9]", GLOB_NOSORT, NULL, handle);
        if (handle.globc != 0)
            LOG(INFO) << handle.globc << " camera(s) found.";
        else
            LOG(WARN) << "No camera found in /dev.";
        list->nCamera = handle.globc;
        list->paths = handle.globv;
        if (!isInit)
            atexit([&handle]() {
                globfree(handle);
            });
        isInit = true;
        return 0;
    }
};  // namespace PiVehicle