#include "pifpv.h"
#include <glog/logging.h>
#include <stdlib.h>
#include <glob.h>

namespace PiVehicle {
    bool isInit = false;
    glob_t *handle;
    int QueryFpvCamera(FpvCameraList *list) {
        LOG(INFO) << "Querying camera...";
        if (!list) {
            // TODO: Log error of null pointer.
            errno = EINVAL;
            return 1;
        }
        glob("/dev/video[0-9]", GLOB_NOSORT, NULL, handle);
        if (handle->gl_pathc != 0)
            LOG(INFO) << handle->gl_pathc << " camera(s) found.";
        else
            LOG(WARNING) << "No camera found in /dev.";
        list->nCamera = handle->gl_pathc;
        list->paths = handle->gl_pathv;
        if (!isInit)
            atexit([]() {
                globfree(handle);
            });
        isInit = true;
        return 0;
    }
};  // namespace PiVehicle