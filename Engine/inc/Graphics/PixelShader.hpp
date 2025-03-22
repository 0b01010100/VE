#pragma once
#include <Prerequisites.hpp>

class PixelShader
{
public:
    PixelShader(std::string_view shader_code, RenderSystem * system);
    ~PixelShader();
    std::string loadShaderFile(std::string_view str);
private:
    unsigned int m_shader = 0;
    RenderSystem * m_system = nullptr;
private:
    friend class RenderSystem;
    friend class DeviceContext;
};