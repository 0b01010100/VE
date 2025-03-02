#include <Window/Window.hpp>
#include <Input/Input.h>
#include <Debug/Console.h>
#include <Graphics/Graphics.hpp>
#include <SDL.h>
#include <glad/glad.h>
#include <vector>

#ifdef main
#undef main
#endif

int main() 
{
    Window wnd;
    Input input; 
    Graphics graphics;

    Console::Log(Console::INFO, "Setting up OpenGL resources...");

    // Define vertex data for a rectangle
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,  // Bottom left
         0.5f, -0.5f, 0.0f,  // Bottom right
         0.5f,  0.5f, 0.0f,  // Top right
        -0.5f,  0.5f, 0.0f   // Top left
    };

    // Define indices for two triangles forming a rectangle
    std::vector<unsigned> indices = {
        0, 1, 2,  // triangle 1 
        2, 3, 0   // triangle 2
    };

    // Create shaders
    VertexShader* vertexShader = graphics.getRenderSystem()->createVertexShader("Shaders\\shader.vs");
    PixelShader* pixelShader = graphics.getRenderSystem()->createPixelShader(default_ps);

    // Initialize render system
    graphics.getRenderSystem()->getPipline()->BindVertexShader(vertexShader);
    graphics.getRenderSystem()->getPipline()->BindPixelShader(pixelShader);
    
    // Define vertex attributes (3D position)
    Attributes attribs = {
        { 0, 3, VG_FLOAT, false }
    };

    // Create vertex buffer
    VertexBuffer* vertexBuffer = graphics.getRenderSystem()->createVertexBuffer(vertices.data(), sizeof(float) * 3, vertices.size(), attribs);
    graphics.getRenderSystem()->getPipline()->BindVertexBuffer(vertexBuffer);

    // Create index buffer
    IndexBuffer* indexBuffer = graphics.getRenderSystem()->createIndexBuffer(indices.data(), sizeof(unsigned int), indices.size());
    graphics.getRenderSystem()->getPipline()->BindIndexBuffer(indexBuffer);

    Console::Log(Console::INFO, "OpenGL resources setup complete");

    float vec[2] = {-1,2};
    UniformBuffer* uniformBuffer = graphics.getRenderSystem()->createUniformBuffer(&vec, sizeof(vec), SaveType::STATIC);
    graphics.getRenderSystem()->getPipline()->BindVUniform(uniformBuffer, 0);
  
    // Main loop
    while (!wnd.shouldClose())
    {
        wnd.pollEvents();
        if (input.isKey(KeyCode::_E, KeyState::Down)) {
            break;
        }

        if (input.isKey(KeyCode::_D, KeyState::Down)) {
            vec[0] += 0.001;
            uniformBuffer->Update(&vec);
        }

        if (input.isKey(KeyCode::_A, KeyState::Down)) {
            vec[0] -= 0.001;
            uniformBuffer->Update(&vec);
        }

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
        // Render using index buffer
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        
        // Swap buffers
        SDL_GL_SwapWindow(wnd.getHandle());
    }

    return 0;
}
