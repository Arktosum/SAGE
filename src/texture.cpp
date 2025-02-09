#include "texture.hpp"
#include "GLManager.hpp"
#include <iostream>
#include <stb_image/stb_image.h>

Texture::Texture(const std::string &file_path)
{
    // Flip the image data because Open GL expects the buffer that way.
    stbi_set_flip_vertically_on_load(true);

    GLCall(glGenTextures(1, &m_texture_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // set texture wrapping to GL_REPEAT (default wrapping method)
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    // set texture filtering parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // load image, create texture and generate mipmaps

    unsigned int desired_channels = 3; // JPG only has 3 channels (RGB) , PNG has 4 channels (RGBA)
    unsigned char *data = stbi_load(file_path.c_str(), &m_width, &m_height, &m_channel_count, desired_channels);
    if (data)
    {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(-1);
    }

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(data);
}
Texture::~Texture()
{
}
void Texture::bind(unsigned int slot) const
{
    // activate a particular texture (0 to 31)
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}
void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}