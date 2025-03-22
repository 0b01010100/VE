#pragma once
#include <Prerequisites.hpp>

class UniformBuffer
{
public:
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
    RenderSystem* m_system;
    unsigned int m_buffer_id = 0;
    unsigned int m_buffer_size = 0;
    SaveType m_save_type = SaveType::STATIC;
private:
    friend class DeviceContext;
    friend class RenderSystem;
};