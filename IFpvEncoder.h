#ifndef PI_VEHICLE_FPV_IFPVENCODER_H
#define PI_VEHICLE_FPV_IFPVENCODER_H

namespace PiVehicle {

    const int FPV_ENCODER_OPENH264 = 1 << 0;
    const int FPV_ENCODER_X264 = 1 << 1;

    int QueryFpvEncoder(int *encoders);
    int CreateFpvEncoder(int type, IFpvEncoder *encoder);

    class IFpvEncoder {
    public:
        virtual ~IFpvEncoder() = 0;


    };
};  // namespace PiVehicle

#endif
