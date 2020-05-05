#include "Headers/Engine/Audio/Listener.h"

void Listener::update(const Camera &camera) noexcept {
    //@todo will be implemented later
}

void Listener::updatePos(const glm::vec3 pos) noexcept {
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}
void Listener::updateVelocity(const glm::vec3 vel) noexcept {
    alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
}
void Listener::updateOrientation(const std::array<ALfloat, 6> &listenerOri) noexcept {
    alListenerfv(AL_ORIENTATION, listenerOri.data());
}
