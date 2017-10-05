#ifndef PI_VEHICLE_FPV_FPVCAMERALINUX_H
#define PI_VEHICLE_FPV_FPVCAMERALINUX_H

#include "IFpvCamera.h"
#include "pifpv.h"
#include <linux/videodev2.h>
#include <vector>

namespace PiVehicle {

    class FpvCameraLinux : public IFpvCamera {
        friend int CreateFpvCamera(const char *path, IFpvCamera *camera);
    public:
        FpvCameraLinux();
        ~FpvCameraLinux();
    protected:
        void setFd(int fd) { _fd = fd; }
        void setV4l2Capability(v4l2_capability capability) { _capability = capability; }
        void setV4l2Format(v4l2_format format) { _format = format; }
        void addV4l2PixelFormat(__u32 pixelformat);
    private:
        int _fd;
        v4l2_capability _capability;
        v4l2_format _format;
        std::vector<__u32> _pixelformat;
    };

};  // namespace PiVehicle

#endif
