#pragma once
#include <Graphics/Defines.h>

class PixelShader
{
private:
    PixelShader(std::string_view shader_code, RenderSystem * system);
    ~PixelShader();
    bool looksLikeFile(std::string_view str);
    std::string loadShaderFile(std::string_view str);
private:
    unsigned int m_shader = 0;
    RenderSystem * m_system = nullptr;
private:
    friend class RenderSystem;
    friend class Pipeline;
};