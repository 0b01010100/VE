#include <Graphics/UniformBuffer.hpp>

UniformBuffer::UniformBuffer
(
    void* buffer, 
    unsigned int buffer_size,
    SaveType save_type, 
    RenderSystem* system
): m_buffer_size(buffer_size), m_system(system), m_save_type(save_type)
{
    if (!system)
        throw std::invalid_argument("Render system is null");

    if (buffer_size == 0)
        throw std::invalid_argument("Buffer size cannot be zero");

    // Create the OpenGL uniform buffer
    glGenBuffers(1, &m_buffer_id);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after glGenBuffers: " + std::to_string(error));

    glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
    error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after glBindBuffer: " + std::to_string(error));

    glBufferData(GL_UNIFORM_BUFFER, buffer_size, buffer, (save_type == STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after glBufferData: " + std::to_string(error));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after unbinding the buffer: " + std::to_string(error));
}

UniformBuffer::~UniformBuffer()
{
    if (m_buffer_id != 0)
    {
        glDeleteBuffers(1, &m_buffer_id);
        m_buffer_id = 0;
    }
}

void UniformBuffer::Update(void* buffer, size_t offset)
{
    if (!buffer)
        throw std::invalid_argument("Buffer data is null");

    glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error before glBufferSubData: " + std::to_string(error));

    m_buffer_size = this->m_buffer_size + ((this->m_save_type == STATIC)? 0x0 : offset);
    glBufferSubData(GL_UNIFORM_BUFFER, 0x0, m_buffer_size, buffer);

    error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after glBufferSubData: " + std::to_string(error));

    glBindBuffer(GL_UNIFORM_BUFFER, 0x0);

    error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL error after unbinding the buffer in Update: " + std::to_string(error));
    
}