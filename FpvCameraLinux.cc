#include "FpvCameraLinux.h"
#include <unistd.h>
#include <memory.h>

namespace PiVehicle {

    FpvCameraLinux::FpvCameraLinux() {
        _fd = 0;
        memset(&_capability, 0, sizeof(_capability));
        memset(&_format, 0, sizeof(_format));
    }

    FpvCameraLinux::~FpvCameraLinux() {
        close(_fd);
    }

    void FpvCameraLinux::addV4l2PixelFormat(__u32 pixelformat) {
        this->_pixelformat.push_back(pixelformat);
    }
}; // namespace PiVehicle
