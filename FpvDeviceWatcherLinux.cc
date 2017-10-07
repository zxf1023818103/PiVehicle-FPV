#include "FpvDeviceWatcherLinux.h"
#include <unistd.h>
#include <sys/inotify.h>

namespace PiVehicle {

    std::thread _worker_thread(FpvDeviceWatcherLinux::worker);

    FpvDeviceWatcherLinux::~FpvDeviceWatcherLinux() {

    }

    FpvDeviceWatcherLinux::FpvDeviceWatcherLinux() {

    }

    int FpvDeviceWatcherLinux::worker() {
        int fd = inotify_init();
        while (true) {
            
        }
    }

};  // namespace PiVehicle