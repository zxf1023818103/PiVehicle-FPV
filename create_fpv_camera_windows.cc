#include "pifpv.h"
#include <Windows.h>
#include <glog/logging.h>

namespace PiVehicle {
    int CreateFpvCamera(const char *path, IFpvCamera *camera) {
        LOG(INFO) << "Opening camera: " << path;

        return 0;
    }
};  // namespace PiVehicle