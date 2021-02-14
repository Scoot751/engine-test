//
// Created by Scoot on 13/02/2021.
//

#include <iostream>

#include <glew.h>
#include <glfw3.h>
#include "window/window.h"

GLFWwindow* Window::window;
int Window::m_nWidth = 0;
int Window::m_nHeight = 0;

int Window::initialize(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    return 0;
}

void Window::setCursorMode(int mode){
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Window::terminate() {
    glfwTerminate();
}

bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}
