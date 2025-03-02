#pragma once
#include <Graphics/Defines.h>

class VertexShader
{
private:
    VertexShader(std::string_view shader_code, RenderSystem * system);
    ~VertexShader();
    bool looksLikeFile(std::string_view str);
    std::string loadShaderFile(std::string_view str);
private:
    unsigned int m_shader;
    RenderSystem * m_system;
private:
    friend class RenderSystem;
    friend class Pipeline;
};