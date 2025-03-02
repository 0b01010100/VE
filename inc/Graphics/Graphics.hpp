#include <Graphics/Defines.h>

class Graphics
{
public:
    Graphics();
    ~Graphics();
public:

    RenderSystem * getRenderSystem() const;

private:
    RenderSystem * m_system = nullptr;
};