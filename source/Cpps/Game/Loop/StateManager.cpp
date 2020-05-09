#include "Headers/Game/Loop/StateManager.h"

StateManager::StateManager(Window* window) {
    gameState = MENU;
    this->window = window;
}

void StateManager::resumeGame(Window& window) {
    gameState = RUNNING;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void StateManager::pauseGame(Window& window) {
    gameState = PAUSED;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void StateManager::display(Window &window) {
    gameState = DISPLAY;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void StateManager::win(Window &window) {
    gameState = WON;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void StateManager::exitGame(Window& window) {
    gameState = QUITING;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

StateManager::State StateManager::getState() {
    return gameState;
}