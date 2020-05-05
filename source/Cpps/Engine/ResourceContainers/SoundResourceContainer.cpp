#include "Headers/Engine/ResourceContainers/SoundResourceContainer.h"

SoundResourceContainer::SoundResourceContainer(const ALuint sourcePar, const ALuint bufferPar) noexcept
: source(sourcePar), buffer(bufferPar)
{}

[[nodiscard]] ALuint SoundResourceContainer::getSource() const noexcept {
    return source;
}
[[nodiscard]] ALuint SoundResourceContainer::getBuffer() const noexcept {
    return buffer;
}

SoundResourceContainer::~SoundResourceContainer() noexcept {
    //CLEAN UP:
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}
