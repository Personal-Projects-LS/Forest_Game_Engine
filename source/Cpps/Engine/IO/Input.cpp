#include "Headers/Engine/IO/Input.h"

std::unique_ptr<Input> Input::instance;

Input::Input() = default;

Input::Input(Window *window, Camera *camera) {
    instance = std::make_unique<Input>();

    instance->m_window = window->getWindow();
    instance->m_camera = camera;

    instance->firstMouse = true;

    instance->lastX = window->getWidth();
    instance->lastY = window->getHeight();

    instance->m_keys.fill(false);
    instance->m_buttons.fill(false);

    glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
    glfwSetScrollCallback(window->getWindow(), scroll_callback);
    glfwSetCursorEnterCallback(window->getWindow(), cursor_enter_callback);
}

void Input::processInput(Player *player, StateManager& manager) {
    for(int i = 0; i < GLFW_KEY_LAST; ++i) {
        instance->m_keys[i] = glfwGetKey(instance->m_window, i) == GLFW_PRESS;
    }
    for(int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
        instance->m_buttons[i] = glfwGetMouseButton(instance->m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }

    if(instance->m_keys[GLFW_KEY_ESCAPE]) {
        manager.pauseGame(*manager.window);
    }

    if(manager.getState() == manager.RUNNING) {
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
            player->setSpeed(Player::SPEED);
        } else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
            player->setSpeed(-Player::SPEED);
        } else {
            player->setSpeed(0);
        }
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
            player->setLateralSpeed(Player::LATERAL_SPEED);
        } else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
            player->setLateralSpeed(-Player::LATERAL_SPEED);
        } else {
            player->setLateralSpeed(0);
        }
    } else {
        player->setSpeed(0);
        player->setLateralSpeed(0);
    }
    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS && !player->isInAir()) {
        player->jump();
    }
    if(glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS) {
        if(cursor && !held) {
            cursor = false;
            held = true;
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else if(!held) {
            cursor = true;
            held = true;
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    } else {
        held = false;
    }
    if(glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT)) {
        if(!cursorHeld && glfwGetTime() - lastShot > 0.5) {
            cursorHeld = true;
            shouldShoot = true;
            lastShot = glfwGetTime();
        }
    } else {
        cursorHeld = false;
    }
}

void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(instance->firstMouse){
        instance->lastX = static_cast<float>(xpos);
        instance->lastY = static_cast<float>(ypos);
        instance->firstMouse = false;
    }
    float xoffset = static_cast<float>(xpos - instance->lastX);
    float yoffset = static_cast<float>(instance->lastY - ypos);
    instance->lastX = static_cast<float>(xpos);
    instance->lastY = static_cast<float>(ypos);

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    instance->m_camera->ProcessMouseMovement(xoffset, yoffset, true);
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    instance->m_camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::cursor_enter_callback(GLFWwindow* window, int entered) {}

bool Input::isKeyDown(int key) {
    return instance->m_keys[key];
}
bool Input::isButtonDown(int button) {
    return instance->m_buttons[button];
}

double Input::getScrollY() {
    return instance->m_scrollY;
}
double Input::getScrollX() {
    return instance->m_scrollX;
}

double Input::getMouseY() {
    return instance->lastY;
}
double Input::getMouseX() {
    return instance->lastX;
}

bool Input::isShouldShoot() {
    return shouldShoot;
}

void Input::setShouldShoot(bool value) {
    shouldShoot = value;
}

std::unique_ptr<Input>& Input::getInstance() {
    return instance;
}