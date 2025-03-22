#include <Graphics/DeviceContext.hpp>
//SWAP CHAIN
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/UniformBuffer.hpp>
#include <Graphics/VertexShader.hpp>
#include <Graphics/PixelShader.hpp>
#include <Graphics/Texture2D.hpp>
#include <glad/glad.h>

DeviceContext::DeviceContext(RenderSystem * system) : m_system(system) 
{
    this->m_ShaderProgram.spo = glCreateProgram();
}

void DeviceContext::setVertexShader(VertexShaderPtr vs)
{
    if (m_ShaderProgram.vs) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.vs);
    }
    
    m_ShaderProgram.vs = vs->m_shader;
    glAttachShader(m_ShaderProgram.spo, vs->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    glUseProgram(m_ShaderProgram.spo);
}

void DeviceContext::setPixelShader(PixelShaderPtr ps)
{
    if (m_ShaderProgram.ps) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.ps);
    }
    
    m_ShaderProgram.ps = ps->m_shader;
    glAttachShader(m_ShaderProgram.spo, ps->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    glUseProgram(m_ShaderProgram.spo);
}

void DeviceContext::setUniformBuffer(UniformBufferPtr ub, unsigned int bindingPoint)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ub->m_buffer_id);
}

void DeviceContext::setVertexBuffer(VertexBufferPtr vb)
{
    glBindVertexArray(vb->m_vba);
    glBindBuffer(GL_ARRAY_BUFFER, vb->m_vbo);
}

void DeviceContext::setIndexBuffer(IndexBufferPtr ib)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->m_ebo);
}

void DeviceContext::setTexture(Texture2DPtr* tex, unsigned int num_textures)
{
    for (unsigned int i = 0; i < num_textures; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);  // Activate texture unit i
        glBindTexture(GL_TEXTURE_2D, tex[i]->m_texture);  // Bind the corresponding texture
    }
}

DeviceContext::~DeviceContext()
{
    glDeleteProgram(this->m_ShaderProgram.spo);
}

void DeviceContext::setRenderMode(RenderMode mode)
{
    if (mode == 0) // Solid mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (mode == 1) // Wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == 2) // Point mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}


void DeviceContext::setCullMode(CullMode mode)
{
    if (mode == CullMode::None) {
        glDisable(GL_CULL_FACE);
        return;
    }

    glEnable(GL_CULL_FACE);

    switch (mode) {
        case CullMode::Front:
            glCullFace(GL_FRONT);
            break;
        case CullMode::Back:
            glCullFace(GL_BACK);
            break;
        case CullMode::None:
            glCullFace(GL_NONE);
            break;
        default:
            break;
    }
}

void DeviceContext::drawTrianlgeList(int vertex_count, int start_vertex_index){
    glDrawArrays(GL_TRIANGLES, start_vertex_index, vertex_count);
}

void DeviceContext::drawIndexedTriangleList(int index_count, int start_vertex_index, int start_index_location){
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)(start_index_location * sizeof(GLuint)));
}

void DeviceContext::drawTrianlgeStrip(int vertex_count, int start_vertex_index){
    glDrawArrays(GL_TRIANGLE_STRIP, start_vertex_index, vertex_count);
}

void DeviceContext::clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha){
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeviceContext::clearDepthStencil(const SwapChainPtr& swap_chain)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void DeviceContext::setViewportSize(int width, int height){
    glViewport(0, 0, width, height);
}