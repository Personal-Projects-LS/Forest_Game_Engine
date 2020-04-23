#pragma once
#include "Headers/Engine/IO/Window.h"
#include <glfw/glfw3.h>

class StateManager {

public:
    enum State {
        RUNNING,
        PAUSED,
        QUITING
    };

    StateManager(Window* window);

    void pauseGame(Window& window);
    void resumeGame(Window& window);
    void exitGame();

    State getState();
    Window* window;

private:
    State gameState;

};
