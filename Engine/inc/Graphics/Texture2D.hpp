#pragma once
#include <Prerequisites.hpp>
#include <Math/Rect.hpp>

class Texture2D 
{
public:
    Texture2D( std::string_view full_path);
    Texture2D(const Rect& size, Type type);
    ~Texture2D();
public:
    Rect getSize();
    Type getType();
private:
    unsigned int m_texture;
    unsigned int m_fbo = 0;
    unsigned int m_rbo = 0;
    Type m_type;
    Rect m_size;

private:
    friend class RenderSystem;
    friend class DeviceContext;
};