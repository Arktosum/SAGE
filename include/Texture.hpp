#pragma once

#include <glad/glad.h>
#include <iostream>
#include "stb_image/stb_image.h"
class Texture
{
public:
    unsigned int texture;
    Texture();
    ~Texture();
    void bind();
    void load_image(const std::string &filepath);
    void setActiveTexture(unsigned int texture_index);
};