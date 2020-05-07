#include "Headers/Game/Loop/Time.h"

void Time::start() {
    lastFrame = glfwGetTime();
}

void Time::update() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float Time::getDeltaTime() {
    return deltaTime;
}