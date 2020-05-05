#pragma once

#include <memory>
#include <iostream>
#include <cstring>

#include <audio/wave.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Headers/Engine/IO/Audio.h"
#include "Headers/Engine/ResourceContainers/SoundResourceContainer.h"

class Sound {
private:
    std::shared_ptr<SoundResourceContainer> soundBufferContainer;

    void bind() const noexcept;

public:
    explicit Sound(const char *filename) noexcept;

    void play() const noexcept;
};
