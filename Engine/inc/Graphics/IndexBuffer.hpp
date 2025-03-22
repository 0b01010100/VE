#pragma once
#include <Prerequisites.hpp>

class IndexBuffer
{
public:
    IndexBuffer
    (
        void* indies, 
        unsigned int index_size, 
        unsigned int index_count, 
        RenderSystem* system
    );
    ~IndexBuffer();
public: 
    void * getIndies() const;
    unsigned int getIndexSize() const;
    unsigned int getSizeIndexList() const;
private:
    unsigned int m_ebo;
    unsigned int m_indexSize;
    unsigned int m_indexCount;
    void* m_data;
    RenderSystem * m_system;
private:
    friend class DeviceContext;
    friend class RenderSystem;
};