#include <Graphics/Pipeline.hpp>

Pipeline::Pipeline(){
    this->m_ShaderProgram.spo = glCreateProgram();
}

void Pipeline::BindVertexShader(VertexShader* vs)
{
    if (!vs) {
        throw std::invalid_argument("Null vertex shader provided");
    }

    if (m_ShaderProgram.vs) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.vs);
    }
    
    m_ShaderProgram.vs = vs->m_shader;
    glAttachShader(m_ShaderProgram.spo, vs->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    
    GLint success;
    glGetProgramiv(m_ShaderProgram.spo, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_ShaderProgram.spo, 512, NULL, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
    glUseProgram(m_ShaderProgram.spo);
}

void Pipeline::BindPixelShader(PixelShader* ps)
{
    if (!ps) {
        throw std::invalid_argument("Null pixel shader provided");
    }

    if (m_ShaderProgram.ps) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.ps);
    }
    
    m_ShaderProgram.ps = ps->m_shader;
    glAttachShader(m_ShaderProgram.spo, ps->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    
    GLint success;
    glGetProgramiv(m_ShaderProgram.spo, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_ShaderProgram.spo, 512, NULL, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
    glUseProgram(m_ShaderProgram.spo);
}

void Pipeline::BindVUniform(UniformBuffer *ub, unsigned int bindingPoint)
{
    if (!ub)
        throw std::invalid_argument("Uniform buffer is null");

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ub->m_buffer_id);
}


void Pipeline::BindVertexBuffer(VertexBuffer* vb)
{
    glBindVertexArray(vb->m_vba);  // Bind the Vertex Array Object
    glBindBuffer(GL_ARRAY_BUFFER, vb->m_vbo);  // Bind the Vertex Buffer Object
}

void Pipeline::BindIndexBuffer(IndexBuffer* ib)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->m_ebo);
}

Pipeline::~Pipeline()
{
    glDeleteProgram(this->m_ShaderProgram.spo);
}

void Pipeline::SetCullMode(CullMode mode)
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
        case CullMode::FrontAndBack:
            glCullFace(GL_FRONT_AND_BACK);
            break;
        default:
            break;
    }
}
