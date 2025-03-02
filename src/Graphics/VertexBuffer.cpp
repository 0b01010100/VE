#include <Graphics/VertexBuffer.hpp>

VertexBuffer::VertexBuffer
(
    void * vertices, 
    size_t vertex_size, 
    size_t vertex_count, 
    Attributes vertex_attribs,
    RenderSystem * system
) : m_system(system) 
  {
    // Create vertex array object 
    glGenVertexArrays(1, &m_vba);
    glBindVertexArray(m_vba);

    // Create vertex buffer object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_size * vertex_count, vertices, GL_STATIC_DRAW);

    // Setup vertex attributes
    size_t offset = 0;
    for (const auto& attrib : vertex_attribs) {
        glEnableVertexAttribArray(attrib.index);
        glVertexAttribPointer(attrib.index, attrib.size, (GLenum)attrib.type, attrib.normalized, vertex_size, (void*)offset);
        offset += attrib.size * sizeof(float);
    }

    // Unbind the vertex array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vba);
}
