#include <Graphics/VertexBuffer.hpp>


// VertexBuffer Constructor Implementation
VertexBuffer::VertexBuffer(
    void* vertices,       // Pointer to vertex data
    size_t vertex_size,   // Size of each vertex
    size_t vertex_count,  // Number of vertices
    Attributes vertex_attribs, // Vertex attributes
    RenderSystem* system  // Render system pointer
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

    // 4. Configure Vertex Attributes
    size_t offset = 0;
    for (const auto& attrib : vertex_attribs) {
        // Enable the vertex attribute array
        glEnableVertexAttribArray(attrib.index);
        
        // Configure the vertex attribute pointer
        glVertexAttribPointer(
            attrib.index,           // Attribute index
            attrib.size,            // Number of components
            static_cast<GLenum>(attrib.type), // Data type
            attrib.normalized,      // Normalized flag
            vertex_size,            // Stride between vertices
            reinterpret_cast<void*>(offset) // Offset within the vertex
        );

        // Calculate offset for next attribute
        offset += attrib.size * sizeof(float);
    }

    // 5. Unbind buffers to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vba);
}
