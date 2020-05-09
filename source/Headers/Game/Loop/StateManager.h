#pragma once
#include "Headers/Engine/IO/Window.h"
#include <glfw/glfw3.h>

class StateManager {

public:
    enum State {
        RUNNING,
        PAUSED,
        QUITING,
        DISPLAY,
        WON,
        MENU
    };

    StateManager(Window* window);

    void pauseGame(Window& window);
    void display(Window& window);
    void resumeGame(Window& window);
    void win(Window& window);
    void exitGame(Window& window);

    State getState();
    Window* window;

private:
    State gameState;

};
