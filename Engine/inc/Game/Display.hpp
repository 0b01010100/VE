#pragma once
#include <Prerequisites.hpp>
#include <Math/Rect.hpp>
#include <Window/Window.hpp>
#include <SDL2/SDL.h>

class Display : public Window
{
public:
	Display ( Game* game, std::string_view name, std::string_view icon_path );
	~Display ( );
protected:
	virtual void onSize ( const Rect& size );
private:
	SwapChainPtr m_swapChain;
	Game* m_game = nullptr; 
private:
	friend class GraphicsEngine;


};