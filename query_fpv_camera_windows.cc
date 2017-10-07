#define GLOG_NO_ABBREVIATED_SEVERITIES

#include "IFpvCamera.h"
#include <windows.h>
#include <glog/logging.h>

namespace PiVehicle {

    int QueryFpvCamera(FpvCameraList *list) {
        LOG(INFO) << "Querying camera...";
        if (!list) {
            // TODO: Log error of null pointer.
            errno = EINVAL;
            return 1;
        }
        // TODO
        return 0;
    }

};  // namespace PiVehicle