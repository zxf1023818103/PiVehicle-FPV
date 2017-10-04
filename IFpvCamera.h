#ifndef PI_VEHICLE_FPV_IFPVCAMERA_H
#define PI_VEHICLE_FPV_IFPVCAMERA_H

namespace PiVehicle {
    class IFpvCamera {
        friend int CreateFpvCamera(const char *path, IFpvCamera *camera);
    public:
        virtual ~IFpvCamera() = 0;
    protected:
        void setPath(const char* path);

    protected:
        char *path;
    };
};  // namespace PiVehicle

#endif
