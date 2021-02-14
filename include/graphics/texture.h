//
// Created by Scoot on 14/02/2021.
//

#ifndef ENGINE_TEST_TEXTURE_H
#define ENGINE_TEST_TEXTURE_H

#include <string>

class Texture {
public:
    unsigned int id;
    int width;
    int height;

public:
    Texture(unsigned int id, int width, int height);
    ~Texture();

    void bind();
};

extern Texture* load_texture(std::string filename);

#endif //ENGINE_TEST_TEXTURE_H
