#include <Window/Window.hpp>
#include <Input/Input.h>
#include <Debug/Console.h>
#include <Graphics/Graphics.hpp>
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

    // Define vertex data for a rectangle with texture coordinates
    std::vector<float> vertices = {
        // Positions         // Texture Coords
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // Bottom left
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // Bottom right
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // Top right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // Top left
    };

    // Define indices for two triangles forming a rectangle
    std::vector<unsigned> indices = {
        0, 1, 2,  // triangle 1 
        2, 3, 0   // triangle 2
    };

    // Create shaders
    VertexShader* vertexShader = graphics.getRenderSystem()->createVertexShader("Shaders\\shader1.vs");
    PixelShader* pixelShader = graphics.getRenderSystem()->createPixelShader("Shaders\\shader1.fs");

    // Initialize render system
    graphics.getRenderSystem()->getPipline()->BindVertexShader(vertexShader);
    graphics.getRenderSystem()->getPipline()->BindPixelShader(pixelShader);
    
    // Define vertex attributes with proper stride and offset
    Attributes attribs = {
        // index, size, type, normalized, stride, offset
        { 0, 3, VG_FLOAT, false, sizeof(float) * 5, (const void*)0 },                  // Position (3 floats)
        { 1, 2, VG_FLOAT, false, sizeof(float) * 5, (const void*)(sizeof(float) * 3) } // Texture coordinates (2 floats)
    };

    // Create vertex buffer with correct vertex size (5 floats per vertex)
    VertexBuffer* vertexBuffer = graphics.getRenderSystem()->createVertexBuffer(
        vertices.data(),
        sizeof(float) * 5,  // Size of each vertex (3 position + 2 texture)
        vertices.size() / 5, // Number of vertices (total floats / floats per vertex)
        attribs
    );
    graphics.getRenderSystem()->getPipline()->BindVertexBuffer(vertexBuffer);

    // Create index buffer
    IndexBuffer* indexBuffer = graphics.getRenderSystem()->createIndexBuffer(indices.data(), sizeof(unsigned int), indices.size());
    graphics.getRenderSystem()->getPipline()->BindIndexBuffer(indexBuffer);
    //graphics.getRenderSystem()->getPipline()->SetRenderMode(WIRE);

    Console::Log(Console::INFO, "OpenGL resources setup complete");

    float vec[2] = {0,0};
    UniformBuffer* uniformBuffer = graphics.getRenderSystem()->createUniformBuffer(&vec, sizeof(vec), SaveType::STATIC);
    graphics.getRenderSystem()->getPipline()->BindVUniform(uniformBuffer, 0);
    
    Texture2D* texture = graphics.getRenderSystem()->createTexture("Textures/MyFirstImage.png");
    graphics.getRenderSystem()->getPipline()->BindTexture2D(texture, 0);

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

        if (input.isKey(KeyCode::_W, KeyState::Down)){
            vec[1] += 0.001;
            uniformBuffer->Update(&vec);
        }

        if (input.isKey(KeyCode::_S, KeyState::Down)){
            vec[1] -= 0.001;
            uniformBuffer->Update(&vec);
        }

        // Clear the screen
        graphics.getRenderSystem()->getPipline()->ClearRenderTargetColor(0,0,0,1);
         
        // Render using index buffer
        graphics.getRenderSystem()->getPipline()->DrawIndexedList(indices.size(), 0, 0);

        // Swap buffers
        SDL_GL_SwapWindow(wnd.getHandle());
    }

    return 0;
}