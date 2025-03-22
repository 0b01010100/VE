#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <Graphics/Texture2D.hpp>
Texture2D::Texture2D( std::string_view full_path) {
    // Enable vertical flip before loading the image
    stbi_set_flip_vertically_on_load(true);

    // 1. Generate a texture object
    glGenTextures(1, &m_texture);
    
    // 2. Bind the texture to the GL_TEXTURE_2D target
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // 3. Load image data using stb_image library
    int width, height, nrChannels;
    unsigned char* data = stbi_load(full_path.data(), &width, &height, &nrChannels, 0);
    
    // 4. Check if image loading was successful
    if (!data) {
        std::cerr << "Failed to load texture: " << full_path << std::endl;
        return;
    }

    // 5. Determine texture format based on number of channels
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    
    // 6. Create the texture image
    glTexImage2D(
        GL_TEXTURE_2D,     // Target
        0,                 // Mipmap level (base level)
        format,            // Internal format
        width,             // Width
        height,            // Height
        0,                 // Border (must be 0)
        format,            // Format of source image
        GL_UNSIGNED_BYTE,  // Data type of source image
        data               // Image data
    );

    // 7. Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // 8. Set texture parameters
    // Wrapping mode for S (x) and T (y) coordinates
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Filtering modes for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 9. Free the image data
    stbi_image_free(data);

    // 10. Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(const Rect& size, Type type) 
    : m_size(size), m_type(type) {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    if (type == Type::Normal || type == Type::RenderTarget) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.width, size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else if (type == Type::DepthStencil) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, size.width, size.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    if (type == Type::RenderTarget || type == Type::DepthStencil) {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        
        if (type == Type::RenderTarget) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
        } else if (type == Type::DepthStencil) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_texture, 0);
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Framebuffer not complete!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

Rect Texture2D::getSize()
{
    return m_size;
}

Type Texture2D::getType()
{
    return m_type;
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_texture);
    if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
}