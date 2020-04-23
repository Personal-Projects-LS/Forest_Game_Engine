#include "Headers/Game/Loop/StateManager.h"

StateManager::StateManager(Window* window) {
    gameState = RUNNING;
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

void StateManager::exitGame() {
    gameState = QUITING;
}

StateManager::State StateManager::getState() {
    return gameState;
}