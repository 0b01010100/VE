#include <Graphics/IndexBuffer.hpp>
#include <glad/glad.h>
IndexBuffer::IndexBuffer
(
    void* indies, 
    unsigned int index_size, 
    unsigned int index_count, 
    RenderSystem* system
)
    : m_data(indies), m_indexSize(index_size), m_indexCount(index_count), m_system(system)
{
    if (!system)
        throw std::invalid_argument("Render system is null");

    if (index_count == 0 || indies == nullptr)
        throw std::invalid_argument("Invalid index data or count");

    // Create OpenGL index buffer
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size * index_count, indies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getIndexSize() const 
{
    return m_indexSize;
}

unsigned int IndexBuffer::getSizeIndexList() const
{
    return m_indexCount;
}

void* IndexBuffer::getIndies() const
{
    return m_data;
}

IndexBuffer::~IndexBuffer()
{
    if (m_ebo != 0)
    {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
}
