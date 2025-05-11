#include <Graphics/UniformBuffer.hpp>
#include <glad/glad.h>

UniformBuffer::UniformBuffer(SaveType save_type, RenderSystem* system):
    m_buffer_id(0), m_buffer_size(0), m_system(system), m_save_type(save_type), m_binding_point(-1)
{
    if (!system)
        throw std::invalid_argument("Render system cannot be null");

    // Create the OpenGL uniform buffer
    glGenBuffers(1, &m_buffer_id);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("Failed to create uniform buffer: OpenGL error " + std::to_string(error));
}

UniformBuffer::UniformBuffer(void* buffer, unsigned int buffer_size, SaveType save_type, RenderSystem* system):
    m_buffer_id(0), m_buffer_size(buffer_size), m_system(system), m_save_type(save_type), m_binding_point(-1)
{
    if (!system)
        throw std::invalid_argument("Render system cannot be null");

    if (buffer_size == 0)
        throw std::invalid_argument("Buffer size cannot be zero");

    if (!buffer && buffer_size > 0)
        throw std::invalid_argument("Buffer data is null but size is non-zero");

    // Create the OpenGL uniform buffer
    glGenBuffers(1, &m_buffer_id);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("Failed to create uniform buffer: OpenGL error " + std::to_string(error));
    
    // Bind and initialize the buffer
    glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        glDeleteBuffers(1, &m_buffer_id);
        m_buffer_id = 0;
        throw std::runtime_error("Failed to bind uniform buffer: OpenGL error " + std::to_string(error));
    }

    GLenum usage = (save_type == STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_UNIFORM_BUFFER, buffer_size, buffer, usage);
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glDeleteBuffers(1, &m_buffer_id);
        m_buffer_id = 0;
        throw std::runtime_error("Failed to allocate uniform buffer data: OpenGL error " + std::to_string(error));
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
    if (m_buffer_id != 0)
    {
        // Unbind the buffer if it's currently bound
        GLint current_binding;
        glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &current_binding);
        if (static_cast<GLuint>(current_binding) == m_buffer_id)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }
        
        glDeleteBuffers(1, &m_buffer_id);
        m_buffer_id = 0;
    }
}

void UniformBuffer::Update(void* buffer, size_t size_to_update)
{
    if (!buffer)
        throw std::invalid_argument("Buffer data cannot be null");

    if (size_to_update == 0)
        throw std::invalid_argument("Update size cannot be zero");

    // If size_to_update is larger than buffer size and this is a dynamic buffer,
    // we might need to reallocate
    if (size_to_update > m_buffer_size && m_save_type == DYNAMIC)
    {
        // Reallocate with new size
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
            throw std::runtime_error("Failed to bind buffer for reallocation: OpenGL error " + std::to_string(error));

        // Create new buffer with new size
        glBufferData(GL_UNIFORM_BUFFER, size_to_update, buffer, GL_DYNAMIC_DRAW);
        error = glGetError();
        if (error != GL_NO_ERROR)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            throw std::runtime_error("Failed to reallocate buffer: OpenGL error " + std::to_string(error));
        }

        m_buffer_size = size_to_update;
    }
    else
    {
        // Update existing buffer
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
            throw std::runtime_error("Failed to bind buffer for update: OpenGL error " + std::to_string(error));

        // Only update up to the actual buffer size
        size_t update_size = (size_to_update < m_buffer_size) ? size_to_update : m_buffer_size;
        glBufferSubData(GL_UNIFORM_BUFFER, 0, update_size, buffer);
        error = glGetError();
        if (error != GL_NO_ERROR)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            throw std::runtime_error("Failed to update buffer data: OpenGL error " + std::to_string(error));
        }
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error("Failed to unbind buffer after update: OpenGL error " + std::to_string(error));
}

unsigned int UniformBuffer::GetBufferSize() const
{
    return m_buffer_size;
}
