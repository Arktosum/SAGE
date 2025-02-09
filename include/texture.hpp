#pragma once
#include <string>
class Texture
{
private:
    unsigned int m_texture_id;
    int m_width, m_height, m_channel_count; // stbi expects them as an integer for some reason.

public:
    Texture(const std::string &file_path);
    ~Texture();
    void bind(unsigned int slot = 0) const;
    void unbind() const;
    inline unsigned int get_width() const { return m_width; };
    inline unsigned int get_height() const { return m_height; };
    inline unsigned int get_channel_count() const { return m_channel_count; };
};