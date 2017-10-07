#ifndef PI_VEHICLE_FPV_IFPVCAMERA_H
#define PI_VEHICLE_FPV_IFPVCAMERA_H

#include <string>
#include <vector>
#include <asm/types.h>

namespace PiVehicle {

    using FpvCameraList = std::vector<std::string>;
    using FpvPixelFormat = __u32;
    using FpvPixelFormatList = std::vector<FpvPixelFormat>;

    struct FpvCameraFrameSize {
        size_t width;
        size_t height;
    };

    int QueryFpvCamera(FpvCameraList &list);
    int CreateFpvCamera(const std::string &path, IFpvCamera *camera);

    class IFpvCamera {
        friend int CreateFpvCamera(const std::string &path, IFpvCamera *camera);
    public:
        IFpvCamera();
        virtual ~IFpvCamera() = 0;
        virtual int getDeviceName(std::string &name)= 0;
    protected:
        void setPath(const std::string &path) { this->path = path; }

    protected:
        std::string path;
    };

};  // namespace PiVehicle

#endif
