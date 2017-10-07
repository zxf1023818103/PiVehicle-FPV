#ifndef PIVEHICLE_FPV_FPVDEVICEWATCHERLINUX_H
#define PIVEHICLE_FPV_FPVDEVICEWATCHERLINUX_H

#include <string>
#include <memory>
#include <thread>
#include "IFpvDeviceWatcher.h"

namespace PiVehicle {

    using FpvDeviceWatcherLinuxPtr = std::shared_ptr<class FpvDeviceWatcherLinux>;

    class FpvDeviceWatcherLinux : public IFpvDeviceWatcher {
        friend int CreateFpvDeviceWatcher(const std::string &path, IFpvDeviceWatcherPtr &watcher);

    public:
        FpvDeviceWatcherLinux();
        ~FpvDeviceWatcherLinux() override;

        static int worker();
    };

};  // namespace PiVehicle

#endif
