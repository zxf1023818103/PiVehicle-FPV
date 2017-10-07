#include "IFpvStreamServer.h"

namespace PiVehicle {
    int QueryFpvStreamServer(int *servers) {
        if (!servers)
            return 1;
#ifdef USE_ORTP
        *server = FPV_STREAM_SERVER_ORTP;
#elif defined USE_JRTPLIB
        *server = FPV_STREAM_SERVER_JRTPLIB;
#elif defined (USE_ORTP && USE_JRTPLIB)
        *server = FPV_STREAM_SERVER_ORTP | FPV_STREAM_SERVER_JRTPLIB;
#endif
        return 0;
    }
};  // namespace PiVehicle