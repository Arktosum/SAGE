
#include "Texture.hpp"

Texture::Texture()
{
    // Create a texture;
    glGenTextures(1, &this->texture);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // // -------------------------------------------------------------------------------------------
    // shader.use(); // don't forget to activate/use the shader before setting uniforms!
    // // either set it manually like so:
    // unsigned int texture_uniform_location = glGetUniformLocation(shader.shaderProgram, "asddsa");
    // std::cout << texture_uniform_location << std::endl;
    // glUniform1i(texture_uniform_location, 0);
}

void Texture::load_image(const std::string &imagepath)
{
    int width = -1, height = -1, nrChannels = -1;
    unsigned char *texture_data = stbi_load(imagepath.c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    /*

    The first argument specifies the texture target; setting this to GL_TEXTURE_2D means this operation will generate a texture on the currently bound texture object at the same target (so any textures bound to targets GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected).
    The second argument specifies the mipmap level for which we want to create a texture for if you want to set each mipmap level manually, but we'll leave it at the base level which is 0.
    The third argument tells OpenGL in what kind of format we want to store the texture. Our image has only RGB values so we'll store the texture with RGB values as well.
    The 4th and 5th argument sets the width and height of the resulting texture. We stored those earlier when loading the image so we'll use the corresponding variables.
    The next argument should always be 0 (some legacy stuff).
    The 7th and 8th argument specify the format and datatype of the source image. We loaded the image with RGB values and stored them as chars (bytes) so we'll pass in the corresponding values.
    The last argument is the actual image data.
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (texture_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data); // for JPG
        //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);  // for PNG
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(-1);
    }

    // Free image memory since we loaded it.
    stbi_image_free(texture_data);
}
Texture::~Texture()
{
}
void Texture::setActiveTexture(unsigned int texture_index)
{
    if (texture_index < 0 || texture_index > 16)
    {
        std::cout << "Failed to set active texture,Unknown texture index: " << texture_index << std::endl;
        exit(-1);
    }
    glActiveTexture(GL_TEXTURE0 + texture_index);
}
void Texture::bind()
{
    // Bind a texture
    glBindTexture(GL_TEXTURE_2D, this->texture);
}