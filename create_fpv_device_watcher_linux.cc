#include "FpvDeviceWatcherLinux.h"
#include <mutex>
#include <glog/logging.h>

namespace PiVehicle {

    FpvDeviceWatcherLinuxPtr _watcher;

    std::mutex _lock_creating, _lock_created;

    int CreateFpvDeviceWatcher(const std::string &path, IFpvDeviceWatcherPtr &watcher) {
        if (!access(path.c_str(), F_OK))
            return 1;
        _lock_creating.lock();
        if (!_lock_created.try_lock()) {
            _watcher = std::make_shared<FpvDeviceWatcherLinux>();
            FpvDeviceWatcherLinux::_worker_thread = std::move(std::thread(FpvDeviceWatcherLinux::worker));
        }
        watcher = _watcher;
        _lock_creating.unlock();
        return 0;
    }

};  // namespace PiVehicle
