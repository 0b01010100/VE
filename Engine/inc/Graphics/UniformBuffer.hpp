#pragma once
#include <Prerequisites.hpp>
#include <cstddef>
#include <stdexcept>

class UniformBuffer 
{
public:
    // Create an empty uniform buffer
    UniformBuffer(SaveType save_type, RenderSystem* system);
    
    // Create and initialize a uniform buffer
    UniformBuffer(void* buffer, unsigned int buffer_size, SaveType save_type, RenderSystem* system);
    
    // Destructor - cleans up OpenGL resources
    ~UniformBuffer();
    
    // Update the buffer data
    void Update(void* buffer, size_t size_to_update);
    
    // Accessors
    unsigned int GetBufferSize() const;

private:
    unsigned int m_buffer_id;
    unsigned int m_buffer_size;
    RenderSystem* m_system;
    SaveType m_save_type;
    int m_binding_point;
private:
    friend class RenderSystem;
    friend class DeviceContext;
};