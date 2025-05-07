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

	auto sky = getResourceManager ( )->createResource< Texture > ( "Assests/sky.jpg" );
	auto sphere = getResourceManager ( )->createResource< Mesh > ("Assests/sphere.obj");
	
	auto skyMat = getResourceManager ( )->createResource< Material > ( "Assests/SkyBox.vs", "Assests/SkyBox.ps");
	skyMat->addTexture (	sky   );
	
	// skybox
	skyMat->setCullMode ( CullMode::None );
	this->m_entity = getWorld ( )->createEntity<Entity> ( );
	auto meshComponent = this->m_entity->createComponent<MeshComponent> ( );
	auto transform = this->m_entity->getTransform ( );
	meshComponent->setMesh ( sphere );
	meshComponent->addMaterial ( skyMat );
		
	transform->setScale ( Vector3D ( 2, 2, 2 ) );
	
	{
		m_entity = getWorld ( )->createEntity<Entity> ( );
		auto lightComponent = m_entity->createComponent<LightComponent> ( );
		lightComponent->setColor ( Vector4D ( 1, 1, 1, 1 ) );
		m_entity->getTransform ( )->setRotation(Vector3D(-0.707f, 0.707f, 0));
	}


	getWorld ( )->createEntity<Player> ( );

	getInputSystem ( )->lockCursor ( m_looked );
}
void MyGame::onUpdate ( f32 deltaTime )
{

	Game::onUpdate ( deltaTime );
	//m_rotation += 1.57 * deltaTime;

	//m_entity->getTransform ( )->setRotation(Vector3D(-0.707f, m_rotation, 0));

	if (getInputSystem ( )->isKeyDown ( Key::Escape )) 
	{
		m_looked = !m_looked;
		getInputSystem ( )->lockCursor ( m_looked  );
	}
}