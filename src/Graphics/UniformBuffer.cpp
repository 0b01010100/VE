#include <Graphics/UniformBuffer.hpp>

UniformBuffer::UniformBuffer
(
    void* buffer, 
    unsigned int buffer_size, 
    RenderSystem* system
): m_buffer_size(buffer_size), m_system(system)
{
    if (!system)
        throw std::invalid_argument("Render system is null");

    if (buffer_size == 0)
        throw std::invalid_argument("Buffer size cannot be zero");

    // Create the OpenGL uniform buffer
    glGenBuffers(1, &m_buffer_id);
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
    glBufferData(GL_UNIFORM_BUFFER, buffer_size, buffer, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("Failed to create uniform buffer: GL error " + std::to_string(error));
}

UniformBuffer::~UniformBuffer()
{
    if (m_buffer_id != 0)
    {
        glDeleteBuffers(1, &m_buffer_id);
        m_buffer_id = 0;
    }
}

void UniformBuffer::Update(void* buffer)
{
    if (!buffer)
        throw std::invalid_argument("Buffer data is null");

    glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_buffer_size, buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetSaveType(SaveType type)
{
    if (type == SaveType::STATIC)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferData(GL_UNIFORM_BUFFER, m_buffer_size, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        this->m_type = SaveType::STATIC;
    }
    else if (type == SaveType::DYNAMIC) 
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferData(GL_UNIFORM_BUFFER, m_buffer_size, nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        this->m_type = SaveType::DYNAMIC;
    }
}
