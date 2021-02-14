//
// Created by Scoot on 13/02/2021.
//

#ifndef ENGINE_TEST_WINDOW_H
#define ENGINE_TEST_WINDOW_H

class GLFWwindow;

class Window {
public:
    static GLFWwindow* window;
    static int m_nWidth;
    static int m_nHeight;

public:
    static int initialize(int width, int height, const char* title);
    static void terminate();
    static void setCursorMode(int mode);
    static bool isShouldClose();
    static void setShouldClose(bool flag);
    static void swapBuffers();
};

#endif //ENGINE_TEST_WINDOW_H
