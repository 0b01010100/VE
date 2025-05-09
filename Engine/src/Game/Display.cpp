#include <Game/Display.hpp>
#include <Game/Game.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/SwapChain.hpp>
Display::Display (Game* game, std::string_view name, std::string_view icon_path) 
: Window(name, icon_path),  m_game( game )
{
	Rect size = getClientSize ( );
}

Display::~Display ( )
{
	
}

void Display::onSize ( const Rect& size )
{
	m_swapChain->resize ( size.width, size.height );
	m_game->onDisplaySize ( size );
}