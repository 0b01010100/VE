#include <MyGame.hpp>
#include <Player.hpp>
#include <time.h>


MyGame::MyGame ( ) : Game("Virtunity Game", "Assets\\virtunity.png")
{
}

MyGame::~MyGame ( )
{
}


void MyGame::onCreate ( )
{
	
	Game::onCreate ( );


	srand ( (ui32)time ( nullptr ) );

	auto sky = getResourceManager ( )->createResource< Texture > ( "Assets\\sky.jpg" );
	auto sphere = getResourceManager ( )->createResource< Mesh > ("Assets\\sphere.obj");
	
	auto skyMat = getResourceManager ( )->createResource< Material > ( "Assets\\SkyBox.vs", "Assets\\SkyBox.ps");
	skyMat->addTexture ( sky );
	
	// skybox
	skyMat->setCullMode ( CullMode::Back );
	this->m_entity = getWorld ( )->createEntity<Entity> ( );
	auto meshComponent = this->m_entity->createComponent<MeshComponent> ( );
	auto transform = this->m_entity->getTransform ( );
	meshComponent->setMesh ( sphere );
	meshComponent->addMaterial ( skyMat );
		
	transform->setScale ( Vector3D ( 5000, 5000, 5000 ) );
	
	// {
	// 	m_entity = getWorld ( )->createEntity<Entity> ( );
	// 	auto lightComponent = m_entity->createComponent<LightComponent> ( );
	// 	lightComponent->setColor ( Vector4D ( 1, 1, 1, 1 ) );
	// 	m_entity->getTransform ( )->setRotation(Vector3D(-0.707f, 0.707f, 0));
	// }


	getWorld ( )->createEntity<Player> ( );

	getInputSystem ( )->lockCursor ( m_looked );
}
void MyGame::onUpdate ( f32 deltaTime )
{

	Game::onUpdate ( deltaTime );
	// m_rotation += 1.57 * deltaTime;

	// m_entity->getTransform ( )->setRotation(Vector3D(-0.707f, m_rotation, 0));

	if (getInputSystem ( )->isKeyDown ( Key::Escape )) 
	{
		m_looked = !m_looked;
		getInputSystem ( )->lockCursor ( m_looked  );
	}
}