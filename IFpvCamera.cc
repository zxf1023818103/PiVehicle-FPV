#include "IFpvCamera.h"
#include <memory.h>
#include <string.h>

namespace PiVehicle {
    IFpvCamera::IFpvCamera() {
        path = calloc(1, sizeof(char));
    }

    IFpvCamera::~IFpvCamera() {
        free(path);
    }

    void IFpvCamera::setPath(const char *path) {
        size_t size = strlen(path) + 1;
        path = realloc(camera->path, size);
        strncpy(camera->path, path, size);
    }
};  // namespace PiVehicle