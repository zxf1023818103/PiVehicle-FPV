#include "FpvCameraLinux.h"
#include <glog/logging.h>
#include <algorithm>
#include <libv4l2.h>

namespace PiVehicle {

    FpvCameraLinux::FpvCameraLinux() = default;

    FpvCameraLinux::~FpvCameraLinux() {
        close(fd);
    }

    void FpvCameraLinux::addV4l2PixelFormat(FpvPixelFormat pixelFormat) {
        this->pixelFormatList.push_back(pixelFormat);
    }

    int FpvCameraLinux::setPixelFormat(FpvPixelFormat pixelFormat) {
        if(std::none_of(pixelFormatList.begin(), pixelFormatList.end(), [&pixelFormat](__u32 item) {
            return item == pixelFormat;
        })) {
            LOG(ERROR) << "Unsupported pixel format.";
            return 1;
        }
        v4l2_format format{};
        memset(&format, 0, sizeof(format));
        format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        format.fmt.pix.pixelformat = pixelFormat;
        if(v4l2_ioctl(fd, VIDIOC_S_FMT, &format)) {
            LOG(ERROR) << "Couldn't set pixel format: " << strerror(errno) << ".";
            return 1;
        }
        return 0;
    }

    int FpvCameraLinux::getPixelFormat(FpvPixelFormat &pixelFormat){
        pixelFormat = 0;
        v4l2_format format {};
        memset(&format, 0, sizeof(format));
        format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (v4l2_ioctl(fd, VIDIOC_G_FMT, &format)) {
            LOG(ERROR) << "Couldn't get current pixel format: " << strerror(errno) << ".";
            return 1;
        }
        pixelFormat = format.fmt.pix.pixelformat;
        return 0;
    }

    int FpvCameraLinux::getFrameSize(FpvCameraFrameSize &size) {
        v4l2_format format {};
        format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (v4l2_ioctl(fd, VIDIOC_G_FMT, &format)) {
            LOG(ERROR) << "Couldn't get frame size: " << strerror(errno) << ".";
            return 1;
        }
        size.width = format.fmt.pix.width;
        size.height = format.fmt.pix.height;
        return 0;
    }

    int FpvCameraLinux::setFrameSize(const FpvCameraFrameSize &size) {
        v4l2_format format {};
        format.fmt.pix.width = static_cast<__u32>(size.width);
        format.fmt.pix.height = static_cast<__u32>(size.height);
        if (v4l2_ioctl(fd, VIDIOC_S_FMT, &format)) {
            LOG(ERROR) << "Couldn't set frame size: " << strerror(errno) << ".";
            return 1;
        }
        return 0;
    }

    int FpvCameraLinux::getDeviceName(std::string &name) {
        v4l2_capability capability {};
        if (v4l2_ioctl(fd, VIDIOC_QUERYCAP, &capability) != 0) {
            LOG(ERROR) << "Couldn't query capabilities of " << path << ": " << strerror(errno) << ". Returned.";
            return 1;
        }
        for (int i = 0; i < (sizeof capability.card / sizeof capability.card[0]); ++i)
            name[i] = capability.card[i];
        return 0;
    }

    int FpvCameraLinux::getAllPixelFormats(FpvPixelFormatList &list) {
        v4l2_fmtdesc formatDescription {};
//        LOG(INFO) << path << " supports " << formatDescription.index + 1 << " pixel format(s):";
        formatDescription.index = 0;
        formatDescription.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        while (v4l2_ioctl(fd, VIDIOC_ENUM_FMT, &formatDescription) != -1) {
            formatDescription.index++;
            list.push_back(formatDescription.pixelformat);
//            LOG(INFO) << "\t\t" << formatDescription.description;
        }
        return 0;
    }

    void FpvCameraLinux::setFd(int fd) {
        this->fd = fd;
    }

}; // namespace PiVehicle
