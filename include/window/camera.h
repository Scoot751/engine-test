//
// Created by Scoot on 14/02/2021.
//

#ifndef ENGINE_TEST_CAMERA_H
#define ENGINE_TEST_CAMERA_H

#include "../lib/glm/glm.hpp"

using namespace glm;

class Camera {
private:
    void updateVectors();
public:
    vec3 front;
    vec3 up;
    vec3 right;

    vec3 position;
    float fov;
    mat4 rotation;

public:
    Camera(vec3 position, float fov);

    void rotate(float x, float y, float z);

    mat4 getProjection();
    mat4 getView();
};

#endif //ENGINE_TEST_CAMERA_H
