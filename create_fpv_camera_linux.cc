#include "pifpv.h"
#include "FpvCameraLinux.h"
#include <glog/logging.h>
#include <fcntl.h>
#include <libv4l2.h>

namespace PiVehicle {
    int CreateFpvCamera(const std::string &path, IFpvCamera *camera) {
        camera = nullptr;
        LOG(INFO) << "Opening camera: " << path;
        int fd = v4l2_open(path.c_str(), O_NONBLOCK | O_RDWR);
        if (errno != 0) {
            LOG(ERROR) << "Couldn't open " << path << ": " << strerror(errno) << ". Returned.";
            return 1;
        }
        v4l2_capability capability {};
        v4l2_format format {};
        v4l2_fmtdesc formatDescription {};
        if (v4l2_ioctl(fd, VIDIOC_QUERYCAP, &capability) != 0) {
            LOG(ERROR) << "Couldn't query capabilities of " << path << ": " << strerror(errno) << ". Returned.";
            return 1;
        }
        if (!capability.capabilities & V4L2_CAP_VIDEO_CAPTURE) {
            LOG(ERROR) << path << " is not a camera. Returned.";
            return 1;
        }
        if (!capability.capabilities & V4L2_CAP_STREAMING) {
            LOG(ERROR) << path << " is not a streaming device. Returned.";
            return 1;
        }
        format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (v4l2_ioctl(fd, VIDIOC_G_FMT, &format) != 0) {
            LOG(ERROR) << "Couldn't get data format: " << strerror(errno) << ". Returned.";
            return 1;
        }
        LOG(INFO) << path << " supports " << formatDescription.index + 1 << " pixel format(s):";
        formatDescription.index = 0;
        formatDescription.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        auto _camera = new FpvCameraLinux();
        _camera->setPath(path);
        _camera->setFd(fd);
        while (v4l2_ioctl(fd, VIDIOC_ENUM_FMT, &formatDescription) != -1) {
            formatDescription.index++;
            _camera->addV4l2PixelFormat(formatDescription.pixelformat);
            LOG(INFO) << "\t\t" << formatDescription.description;
        }
        camera = _camera;
        return 0;
    }

    void PrintCameraCapabilities(const struct v4l2_capability *capability) {
        LOG(INFO) << "Driver:\t\t" << capability->driver;
        LOG(INFO) << "Card:\t\t" << capability->card;
        LOG(INFO) << "Bus:\t\t" << capability->bus_info;
//        LOG(INFO) << "Version:\t\t"
//                  << (int)(capability->version >> 16) & 0xFF << "."
//                  << (int)(capability->version >> 8) & 0xFF << "."
//                  << (int)capability->version & 0xFF;
        LOG(INFO) << "Capabilities:";
        const unsigned int capabilities[] = {
                        V4L2_CAP_VIDEO_CAPTURE,
                        V4L2_CAP_VIDEO_OUTPUT,
                        V4L2_CAP_VIDEO_OVERLAY,
                        V4L2_CAP_VBI_CAPTURE,
                        V4L2_CAP_VBI_OUTPUT,
                        V4L2_CAP_SLICED_VBI_CAPTURE,
                        V4L2_CAP_SLICED_VBI_OUTPUT,
                        V4L2_CAP_RDS_CAPTURE,
                        V4L2_CAP_VIDEO_OUTPUT_OVERLAY,
                        V4L2_CAP_HW_FREQ_SEEK,
                        V4L2_CAP_RDS_OUTPUT,
                        V4L2_CAP_VIDEO_CAPTURE_MPLANE,
                        V4L2_CAP_VIDEO_OUTPUT_MPLANE,
                        V4L2_CAP_VIDEO_M2M_MPLANE,
                        V4L2_CAP_VIDEO_M2M,
                        V4L2_CAP_TUNER,
                        V4L2_CAP_AUDIO,
                        V4L2_CAP_RADIO,
                        V4L2_CAP_MODULATOR,
                        V4L2_CAP_SDR_CAPTURE,
                        V4L2_CAP_EXT_PIX_FORMAT,
                        V4L2_CAP_SDR_OUTPUT,
                        V4L2_CAP_READWRITE,
                        V4L2_CAP_ASYNCIO,
                        V4L2_CAP_STREAMING,
                        V4L2_CAP_DEVICE_CAPS
                };
        const char *str_capabilities[] = {
                "V4L2_CAP_VIDEO_CAPTURE",
                "V4L2_CAP_VIDEO_OUTPUT",
                "V4L2_CAP_VIDEO_OVERLAY",
                "V4L2_CAP_VBI_CAPTURE",
                "V4L2_CAP_VBI_OUTPUT",
                "V4L2_CAP_SLICED_VBI_CAPTURE",
                "V4L2_CAP_SLICED_VBI_OUTPUT",
                "V4L2_CAP_RDS_CAPTURE",
                "V4L2_CAP_VIDEO_OUTPUT_OVERLAY",
                "V4L2_CAP_HW_FREQ_SEEK",
                "V4L2_CAP_RDS_OUTPUT",
                "V4L2_CAP_VIDEO_CAPTURE_MPLANE",
                "V4L2_CAP_VIDEO_OUTPUT_MPLANE",
                "V4L2_CAP_VIDEO_M2M_MPLANE",
                "V4L2_CAP_VIDEO_M2M",
                "V4L2_CAP_TUNER",
                "V4L2_CAP_AUDIO",
                "V4L2_CAP_RADIO",
                "V4L2_CAP_MODULATOR",
                "V4L2_CAP_SDR_CAPTURE",
                "V4L2_CAP_EXT_PIX_FORMAT",
                "V4L2_CAP_SDR_OUTPUT",
                "V4L2_CAP_READWRITE",
                "V4L2_CAP_ASYNCIO",
                "V4L2_CAP_STREAMING",
                "V4L2_CAP_DEVICE_CAPS"
        };
        for (int i = 0; i < 26; ++i) {
            if (capabilities[i] & capability->capabilities)
                LOG(INFO) << "\t\t" << str_capabilities[i];
        }
    }
};  // namespace PiVehicle