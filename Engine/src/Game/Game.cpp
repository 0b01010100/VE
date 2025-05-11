#include <Game/Game.hpp>
#include <Window/Window.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Game/Display.hpp>
#include <Resource/ResourceManager.hpp>
#include <Resource/Mesh.hpp>
#include <Resource/Texture.hpp>
#include <Resource/Material.hpp>
#include <Input/InputSystem.hpp>
#include <Game/World.hpp>

Game::Game ( std::string_view name, std::string_view icon_path )
{
	m_inputSystem = std::make_unique<  InputSystem > ( );
	m_display = std::make_unique < Display > ( this, name, icon_path );
	m_graphicsEngine = std::make_unique < GraphicsEngine > ( this );
	m_resourceManager = std::make_unique < ResourceManager > ( this );
	m_world = std::make_unique < World > ( this );

	union cast{
		Rect<> ri;
		Rect<float> rf;
	}type_cast = {.ri = m_display->getClientSize ( )};
	m_inputSystem->SetlockArea ( type_cast.rf );
}
Game::~Game ( ) {}
GraphicsEngine* Game::getGraphicsEngine ( )
{
	return this->m_graphicsEngine.get ( );
}
World* Game::getWorld ( )
{
	return m_world.get();
}
InputSystem* Game::getInputSystem ( )
{
	return m_inputSystem.get();
}
ResourceManager* Game::getResourceManager ( )
{
	return m_resourceManager.get();
}
void Game::onDisplaySize ( const Rect<>& size )
{
	union cast{
		Rect<> ri;
		Rect<float> rf;
	}type_cast = {.ri = m_display->getClientSize ( )};
	m_inputSystem->SetlockArea ( type_cast.rf );
	onInternalUpdate ( );
}
void Game::onInternalUpdate ( )
{
	//COMPUTING DELTA TIME
	auto currentTime = std::chrono::system_clock::now ( );
	auto elapsedSeconds = std::chrono::duration<double> ( );//elapsed Time

	if (m_previousTime.time_since_epoch ( ).count ( ))//if m_previousTime is not zero do elapsedSeconds = currentTime - m_previousTime;
		elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	auto deltaTime = (f32)elapsedSeconds.count ( );


	m_inputSystem->update ( );

	onUpdate ( deltaTime );
	m_world->update ( deltaTime );

	m_graphicsEngine->update ( );
}

void Game::quit() 
{
	m_isRunning = false;
}