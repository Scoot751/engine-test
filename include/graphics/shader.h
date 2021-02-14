//
// Created by Scoot on 14/02/2021.
//

#ifndef ENGINE_TEST_SHADER_H
#define ENGINE_TEST_SHADER_H

#include <string>
#include "../lib/glm/glm.hpp"

class Shader {
public:
    unsigned int id;

public:
    Shader(unsigned int id);
    ~Shader();

    void use();
    void uniformMatrix(std::string name, glm::mat4 matrix);
};

extern Shader* loadShader(std::string vertexFile, std::string fragmentFile);

#endif //ENGINE_TEST_SHADER_H
