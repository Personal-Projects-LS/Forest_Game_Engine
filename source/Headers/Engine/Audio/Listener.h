#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <array>

#include "Headers/Engine/Camera/Camera.h"

namespace Listener {
    void update(const Camera &camera) noexcept;

    void updatePos(glm::vec3 pos) noexcept;
    void updateVelocity(glm::vec3 vel) noexcept;
    void updateOrientation(const std::array<ALfloat, 6> &listenerOri) noexcept;
}
