#pragma once
#include <glfw/glfw3.h>

static float deltaTime;
static float lastFrame = 0;
static float currentFrame;

class Time {
public:
    static void start();
    static void update();
    static float getDeltaTime();
};
