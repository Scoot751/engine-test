//
// Created by Scoot on 14/02/2021.
//

#include <string.h>

#include "window/events.h"
#include "glfw3.h"

bool* Events::m_bKeys;
uint* Events::m_nFrames;
uint Events::m_nCurrentFrame = 0;
float Events::m_fDeltaX = 0.0f;
float Events::m_fDeltaY = 0.0f;
float Events::m_fAxisX = 0.0f;
float Events::m_fAxisY = 0.0f;
bool Events::m_bCursorLocked = false;
bool Events::m_bCursorStarted = false;

#define MOUSE_BUTTONS 1024

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (Events::m_bCursorStarted) {
        Events::m_fDeltaX += xpos - Events::m_fAxisX;
        Events::m_fDeltaY += ypos - Events::m_fAxisY;
    }
    else {
        Events::m_bCursorStarted = true;
    }
    Events::m_fAxisX = xpos;
    Events::m_fAxisY = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        Events::m_bKeys[MOUSE_BUTTONS + button] = true;
        Events::m_nFrames[MOUSE_BUTTONS + button] = Events::m_nCurrentFrame;
    }
    else if (action == GLFW_RELEASE) {
        Events::m_bKeys[MOUSE_BUTTONS + button] = false;
        Events::m_nFrames[MOUSE_BUTTONS + button] = Events::m_nCurrentFrame;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        Events::m_bKeys[key] = true;
        Events::m_nFrames[key] = Events::m_nCurrentFrame;
    }
    else if (action == GLFW_RELEASE) {
        Events::m_bKeys[key] = false;
        Events::m_nFrames[key] = Events::m_nCurrentFrame;
    }
}

void window_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0, width, height);
    Window::m_nWidth = width;
    Window::m_nHeight = height;
}

int Events::initialize() {
    GLFWwindow* window = Window::window;
    m_bKeys = new bool[1032];
    m_nFrames = new uint[1032];

    memset(m_bKeys, false, 1032 * sizeof(bool));
    memset(m_nFrames, 0, 1032 * sizeof(uint));

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    return 0;
}

bool Events::isPressed(int keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
        return false;
    return m_bKeys[keycode];
}

bool Events::justPressed(int keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
        return false;
    return m_bKeys[keycode] && m_nFrames[keycode] == m_nCurrentFrame;
}

bool Events::isClicked(int button) {
    int index = MOUSE_BUTTONS + button;
    return m_bKeys[index];
}

bool Events::justClicked(int button) {
    int index = MOUSE_BUTTONS + button;
    return m_bKeys[index] && m_nFrames[index] == m_nCurrentFrame;
}

void Events::toogleCursor(){
    m_bCursorLocked = !m_bCursorLocked;
    Window::setCursorMode(m_bCursorLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::pullEvents() {
    m_nCurrentFrame++;
    m_fDeltaX = 0.0f;
    m_fDeltaY = 0.0f;
    glfwPollEvents();
}