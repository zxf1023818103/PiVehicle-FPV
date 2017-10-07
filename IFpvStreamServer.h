#ifndef PI_VEHICLE_FPV_IFPVSTREAMSERVER_H
#define PI_VEHICLE_FPV_IFPVSTREAMSERVER_H

namespace PiVehicle {

    const int FPV_STREAM_SERVER_ORTP = 1 << 2;
    const int FPV_STREAM_SERVER_JRTPLIB = 1 << 3;

    int CreateFpvStreamServer(int type, IFpvStreamServer *server);
    int QueryFpvStreamServer(int *servers);

    class IFpvStreamServer {
    public:
        virtual ~IFpvStreamServer() = 0;


    };
};  // namespace PiVehicle

#endif
