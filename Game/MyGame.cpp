#include <MyGame.hpp>
#include <Player.hpp>
#include <time.h>


MyGame::MyGame ( )
{
}

MyGame::~MyGame ( )
{
}

void MyGame::onCreate ( )
{
	Game::onCreate ( );


	srand ( (ui32)time ( nullptr ) );


	auto mesh = getResourceManager()->createResourceFromFile< Mesh > ( "Assests/cube.obj" );


	getInputSystem ( )->lockCursor ( m_looked );
}
void MyGame::onUpdate ( f32 deltaTime )
{

	Game::onUpdate ( deltaTime );
	m_rotation += 1.57 * deltaTime;

	//m_entity->getTransform ( )->setRotation(Vector3D(-0.707f, m_rotation, 0));

	if (getInputSystem ( )->isKeyDown ( Key::Escape )) 
	{
		m_looked = !m_looked;
		getInputSystem ( )->lockCursor ( m_looked  );
	}
}