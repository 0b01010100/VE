#pragma once
#include <Prerequisites.hpp>

class VertexShader
{
public:
    VertexShader(std::string_view shader_code, RenderSystem * system);
    ~VertexShader();
    std::string loadShaderFile(std::string_view str);
private:
    RenderSystem * m_system;
    unsigned int m_shader;
private:
    friend class RenderSystem;
    friend class DeviceContext;
};