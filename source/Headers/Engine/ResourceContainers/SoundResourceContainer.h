#pragma once

#include <AL/al.h>

class SoundResourceContainer {
private:
    const ALuint source{}, buffer{};

public:
    SoundResourceContainer(const SoundResourceContainer&) = delete;
    SoundResourceContainer& operator=(const SoundResourceContainer&) = delete;

    SoundResourceContainer(ALuint sourcePar, ALuint bufferPar) noexcept;

    [[nodiscard]] ALuint getSource() const noexcept;
    [[nodiscard]] ALuint getBuffer() const noexcept;

    ~SoundResourceContainer() noexcept;
};
