#include <Graphics/VertexBuffer.hpp>

// VertexBuffer Constructor Implementation
VertexBuffer::VertexBuffer(
    void* vertices,
    size_t vertex_size,
    size_t vertex_count,
    Attributes vertex_attribs,
    RenderSystem* system
) : m_system(system)
{
    // 1. Create and Bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_vba);
    glBindVertexArray(m_vba);

    // 2. Create and Bind Vertex Buffer Object (VBO)
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    // 3. Upload Vertex Data to GPU
    glBufferData(
        GL_ARRAY_BUFFER,           // Buffer type
        vertex_size * vertex_count, // Total buffer size
        vertices,                   // Source data
        GL_STATIC_DRAW              // Usage hint
    );
    
    // 4. Set up vertex attributes based on the provided configuration
    for (const auto& attrib : vertex_attribs) {
        glEnableVertexAttribArray(attrib.index);
        glVertexAttribPointer(
            attrib.index,
            attrib.size,
            attrib.type,
            attrib.normalized,
            attrib.stride,
            attrib.offset
        );
    }

    // 5. Unbind buffers to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vba);
}
