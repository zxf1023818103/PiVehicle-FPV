#include "IFpvEncoder.h"

namespace PiVehicle {
    int QueryFpvEncoder(int *encoders) {
        if (!encoders)
            return 1;
#ifdef USE_OPENH264
        *encoders = FPV_ENCODER_OPENH264;
#elif defined USE_JRTPLIB
        *encoders = FPV_ENCODER_X264;
#elif defined(USE_OPENH264 && USE_JRTPLIB)
        *encoders = FPV_ENCODER_OPENH264 | FPV_ENCODER_X264;
#endif
        return 0;
    }
};  // namespace PiVehicle