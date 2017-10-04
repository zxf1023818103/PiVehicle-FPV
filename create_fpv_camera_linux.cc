#include "pifpv.h"
#include "FpvCameraLinux.h"
#include <glog/logging.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <libv4l2.h>

namespace PiVehicle {
    int CreateFpvCamera(const char *path, IFpvCamera *camera) {
        LOG(INFO) << "Opening camera: " << path;
        int fd = v4l2_open(path, O_NONBLOCK | O_RDWR);
        if (errno != 0) {
            LOG(ERROR) << "Couldn't open " << path << ": " << strerror(errno) << ". Returned.";
            return 1;
        }
        struct v4l2_capability capability;
        struct v4l2_format format;
        struct v4l2_fmtdesc fmtdesc;
        memset(&capability, 0, sizeof(capability));
        memset(&format, 0, sizeof(format));
        memset(&fmtdesc, 0, sizeof(fmtdesc));
        int res = v4l2_ioctl(fd, VIDIOC_QUERYCAP, &capability);
        if (res != 0) {
            LOG(ERROR) << "Couldn't query capabilities of " << path << ": " << strerror(errno) << ". Returned.";
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
        res = v4l2_ioctl(fd, VIDIOC_G_FMT, &camera->format);
        if (res != 0) {
            LOG(ERROR) << "Couldn't get data format: " << strerror(errno) << ". Returned.";
            return 1;
        }
        fmtdesc.index = 0;
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
            fmtdesc.index++;
        LOG(INFO) << "Support " << fmtdesc.index + 1 << " pixel format(s):";
        camera = new FpvCameraLinux();
        camera->setPath(path);
        camera->setFd(fd);
        camera->setV4l2Capability(capability);
        camera->setV4l2Format(format);
        for (int i = 0; i < camera->_n_pixelformats; ++i) {
            fmtdesc.index = i;
            v4l2_ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc);
            camera->addV4l2PixelFormat(fmtdesc.pixelformat);
            LOG(INFO) << "\t\t" << fmtdesc.description;
        }
        return 0;
    }

    void PrintCameraCapabilities(const struct v4l2_capability *capability) {
        LOG(INFO) << "Driver:\t\t" << capability->driver;
        LOG(INFO) << "Card:\t\t" << capability->card;
        LOG(INFO) << "Bus:\t\t" << capability->bus_info;
        LOG(INFO) << "Version:\t\t"
                  << (int)(capability->version >> 16) & 0xFF << "."
                  << (int)(capability->version >> 8) & 0xFF << "."
                  << (int)capability->version & 0xFF;
        LOG(INFO) << "Capabilities:";
        const int capabilities[] = {
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