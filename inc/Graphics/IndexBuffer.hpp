#pragma once
#include <Graphics/Defines.h>

class IndexBuffer
{
private:
    IndexBuffer(void* indies, unsigned int index_size, unsigned int index_count, RenderSystem* system);
    ~IndexBuffer();

public: 
    void * GetIndies() const;
    unsigned int GetIndexSize() const;
    unsigned int GetIndexCount() const;

private:
    GLuint m_ebo;
    unsigned int m_indexSize;
    unsigned int m_indexCount;
    void* m_data;
    RenderSystem * m_system;

private:
    friend class Pipeline;
    friend class RenderSystem;
};