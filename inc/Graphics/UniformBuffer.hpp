#pragma once
#include <Graphics/Defines.h>

class UniformBuffer
{
private:
    UniformBuffer(void* buffer, unsigned int buffer_size, RenderSystem* system);
    ~UniformBuffer();

public:

    void Update(void* buffer);

    void SetSaveType(SaveType type);
    
    // Accessor for the buffer ID (to be used by other classes for binding)
    GLuint GetBufferID() const { return m_buffer_id; }
    unsigned int GetSize() const { return m_buffer_size; }

private:
    GLuint m_buffer_id = 0;
    unsigned int m_buffer_size = 0;
    RenderSystem* m_system = nullptr;
    SaveType m_type;
    
private:
    friend class Pipline;
    friend class RenderSystem;
};