#ifndef PI_VEHICLE_FPV_PI_FPV_H
#define PI_VEHICLE_FPV_PI_FPV_H

#include "IFpvCamera.h"
#include "IFpvEncoder.h"
#include "IFpvStreamServer.h"
#include <vector>
#include <string>

namespace PiVehicle {

    using FpvCameraList = std::vector<std::string>;

    const int FPV_ENCODER_OPENH264 = 1 << 0;
    const int FPV_ENCODER_X264 = 1 << 1;
    const int FPV_STREAM_SERVER_ORTP = 1 << 2;
    const int FPV_STREAM_SERVER_JRTPLIB = 1 << 3;

    int CreateFpvCamera(const std::string &path, IFpvCamera *camera);
    int CreateFpvEncoder(int type, IFpvEncoder *encoder);
    int CreateFpvStreamServer(int type, IFpvStreamServer *server);
    int QueryFpvCamera(FpvCameraList &list);
    int QueryFpvEncoder(int *encoders);
    int QueryFpvStreamServer(int *servers);
};  // namespace PiVehicle

#endif