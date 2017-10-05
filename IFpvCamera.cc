#include "IFpvCamera.h"
#include <memory>
#include <cstring>

namespace PiVehicle {
    IFpvCamera::IFpvCamera() {
        path = static_cast<char *>(calloc(1, sizeof(char)));
    }

    IFpvCamera::~IFpvCamera() {
        free(path);
    }

    void IFpvCamera::setPath(const char *path) {
        size_t size = strlen(path) + 1;
        path = static_cast<const char *>(realloc((void *)this->path, size));
        strncpy(this->path, path, size);
    }
};  // namespace PiVehicle