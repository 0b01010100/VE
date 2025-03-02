#pragma once
#include <Graphics/Defines.h>

class UniformBuffer
{
private:
    UniformBuffer
    (
        void* buffer, 
        unsigned int buffer_size, 
        SaveType save_type, 
        RenderSystem* system
    );

    ~UniformBuffer();

public:

    void Update(void* buffer, size_t size);
    inline void Update(void* buffer){Update(buffer, 0);}

    unsigned int GetSize() const { return m_buffer_size; }
    SaveType GetSaveType() const { return m_save_type;}

private:
    GLuint m_buffer_id = 0;
    unsigned int m_buffer_size = 0;
    RenderSystem* m_system = nullptr;
    SaveType m_save_type = SaveType::STATIC;
    
private:
    friend class Pipeline;
    friend class RenderSystem;
};