#ifndef PIVEHICLE_FPV_IFPVDEVICEWATCHER_H
#define PIVEHICLE_FPV_IFPVDEVICEWATCHER_H

#include <string>
#include <memory>

namespace PiVehicle {

    using IFpvDeviceWatcherPtr = std::shared_ptr<class IFpvDeviceWatcher>;

    int CreateFpvDeviceWatcher(const std::string &path, IFpvDeviceWatcherPtr &watcher);

    class IFpvDeviceWatcher {
        friend int CreateFpvDeviceWatcher(const std::string &path, IFpvDeviceWatcherPtr &watcher);

    public:
        virtual ~IFpvDeviceWatcher() = 0;
    };

};  // namespace PiVehicle

#endif
