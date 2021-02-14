#include <iostream>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

// GLM
#include "../lib/glm/glm.hpp"
#include "../lib/glm/ext.hpp"
using namespace glm;

#include "window/window.h"
#include "window/events.h"
#include "window/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"

#include "loaders/png_loader.h"

int windowWidth = 1280;
int windowHeight = 720;

float vertices[] = {
        // x    y     z     u     v
        -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main() {
    Window::initialize(windowWidth, windowHeight, "Window");
    Events::initialize();

    glClearColor(0.6f, 0.62f, 0.65f, 1);

    Shader* shader = loadShader("../resource/shaders/main.glslv", "../resource/shaders/main.glslf");
    if (shader == nullptr) {
        std::cerr << "Failed to load shader!" << std::endl;
        Window::terminate();
        return 1;
    }

    Texture* texture = loadTexture("../resource/textures/img.png");
    if (texture == nullptr){
        std::cerr << "failed to load texture" << std::endl;
        delete shader;
        Window::terminate();
        return 1;
    }

    // Create VAO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glClearColor(0.6f,0.62f,0.65f,1);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera* camera = new Camera(vec3(0,0,1), radians(90.0f));

    mat4 model(1.0f);
    model = translate(model, vec3(0.5f,0,0));

    float lastTime = glfwGetTime();
    float delta = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;

    float speed = 5;

    while (!Window::isShouldClose()){
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        if (Events::justPressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if (Events::justPressed(GLFW_KEY_TAB)){
            Events::toogleCursor();
        }

        if (Events::isPressed(GLFW_KEY_W)){
            camera->position += camera->front * delta * speed;
        }
        if (Events::isPressed(GLFW_KEY_S)){
            camera->position -= camera->front * delta * speed;
        }
        if (Events::isPressed(GLFW_KEY_D)){
            camera->position += camera->right * delta * speed;
        }
        if (Events::isPressed(GLFW_KEY_A)){
            camera->position -= camera->right * delta * speed;
        }

        if (Events::m_bCursorLocked){
            camY += -Events::m_fDeltaY / Window::m_nHeight * 2;
            camX += -Events::m_fDeltaX / Window::m_nHeight * 2;

            if (camY < -radians(89.0f)){
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)){
                camY = radians(89.0f);
            }

            camera->rotation = mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw VAO
        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("projview", camera->getProjection()*camera->getView());
        texture->bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        Window::swapBuffers();
        Events::pullEvents();
    }

    delete shader;
    delete texture;
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    Window::terminate();
    return 0;
}
