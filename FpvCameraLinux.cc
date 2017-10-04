#include "FpvCameraLinux.h"
#include <unistd.h>
#include <memory.h>

namespace PiVehicle {
    FpvCameraLinux::FpvCameraLinux() {
        _fd = 0;
        _n_pixelformats = 0;
        _pixelformats = calloc(1, sizeof(__u32));
        memset(_capability, 0, sizeof(_capability));
        memset(_format, 0, sizeof(_format));
    }

    FpvCameraLinux::~FpvCameraLinux() {
        close(_fd);
        free(_pixelformats);
    }

    void FpvCameraLinux::addV4l2PixelFormat(__u32 pixelformat) {
        pixelformat.push_back(pixelformat);
    }
}; // namespace PiVehicle
