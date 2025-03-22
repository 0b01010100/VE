#pragma once
#include <Prerequisites.hpp>

class VertexBuffer
{
public:
    VertexBuffer
    (
        void * vertices, 
        size_t vertex_size, 
        size_t vertex_count, 
        Attributes vertex_attribs,
        RenderSystem * system
    );
    ~VertexBuffer();
private:  
    Attributes m_vertex_attribs;
    RenderSystem * m_system = nullptr;
    unsigned int m_vba = 0, m_vbo = 0;
private:
    friend class RenderSystem;
    friend class DeviceContext;
};