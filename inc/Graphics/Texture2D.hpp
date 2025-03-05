#pragma once
#include <Graphics/Defines.h>
#include <optional>
class Texture2D 
{
private:
    Texture2D(const std::string_view full_path);
    Texture2D(int width, int height, VType type);
    ~Texture2D();

private:
    GLuint m_texture;
    GLuint m_fbo = 0;
    GLuint m_rbo = 0;
    VType m_type;
    int m_width, m_height;

private:
    friend class RenderSystem;
    friend class Pipeline;
};