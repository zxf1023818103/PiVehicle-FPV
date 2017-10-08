#include "FpvDeviceWatcherLinux.h"
#include <glog/logging.h>
#include <libudev.h>
#include <sys/select.h>

namespace PiVehicle {

    FpvDeviceWatcherLinux::~FpvDeviceWatcherLinux() {

    }

    FpvDeviceWatcherLinux::FpvDeviceWatcherLinux() {

    }

    int FpvDeviceWatcherLinux::worker() {
        udev *udev = udev_new();
        if (udev == nullptr) {
            LOG(ERROR) << "libudev initialize failed: " << strerror(errno) << ". Returned.";
            return 1;
        }
        udev_monitor *monitor = udev_monitor_new_from_netlink(udev, "PiVehicleDeviceWatcher");
        udev_monitor_filter_add_match_subsystem_devtype(monitor, "video4linux", nullptr);
        udev_monitor_enable_receiving(monitor);
        int fd = udev_monitor_get_fd(monitor);
        fd_set fds;
        timeval tv;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        while (true) {
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            int res = select(fd+1, &fds, NULL, NULL, &tv);
            if (res > 0 && FD_ISSET(fd, &fds)) {
                udev_device *dev = udev_monitor_receive_device(monitor);
                if (dev != nullptr) {
                    
                    udev_device_unref(dev);
                }
            }
        }
        return 0;
    }

};  // namespace PiVehicle