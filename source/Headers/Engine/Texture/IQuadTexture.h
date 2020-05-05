#pragma once

#include "Headers/Engine/Shader/Shader.h"

struct IQuadTexture {
    virtual void bind(const Shader &shader) const noexcept = 0;
    virtual void unbind() const noexcept = 0;

    virtual ~IQuadTexture() = default;
};
