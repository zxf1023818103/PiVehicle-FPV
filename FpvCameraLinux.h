#ifndef PI_VEHICLE_FPV_FPVCAMERALINUX_H
#define PI_VEHICLE_FPV_FPVCAMERALINUX_H

#include "IFpvCamera.h"
#include <linux/videodev2.h>
#include <vector>

namespace PiVehicle {

    class FpvCameraLinux : public IFpvCamera {
        friend int CreateFpvCamera(const std::string &path, IFpvCamera *camera);
    public:
        FpvCameraLinux();
        ~FpvCameraLinux() override;
        int getDeviceName(std::string &name) override;
        int getAllPixelFormats(FpvPixelFormatList &list);
        int setPixelFormat(FpvPixelFormat pixelFormat);
        int getPixelFormat(FpvPixelFormat &pixelFormat);
        int setFrameSize(const FpvCameraFrameSize &size);
        int getFrameSize(FpvCameraFrameSize &size);

    protected:
        void setFd(int fd);
        void addV4l2PixelFormat(__u32 pixelFormat);
    private:
        int fd = 0;
        v4l2_capability capability {};
        v4l2_format format {};
        FpvPixelFormatList pixelFormatList;
    };

};  // namespace PiVehicle

#endif
