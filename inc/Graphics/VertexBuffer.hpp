#pragma once
#include <Graphics/Defines.h>

class VertexBuffer
{
private:
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
    unsigned int m_vba = 0, m_vbo = 0;
    Attributes m_vertex_attribs;
    RenderSystem * m_system = nullptr;
private:
    friend class RenderSystem;
    friend class Pipeline;
};