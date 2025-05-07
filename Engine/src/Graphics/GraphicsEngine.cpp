#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/DeviceContext.hpp>
#include <Graphics/SwapChain.hpp>

#include <Resource/ResourceManager.hpp>
#include <Resource/Mesh.hpp>
#include <Resource/Texture.hpp>
#include <Graphics/Texture2D.hpp>
#include <Resource/Material.hpp>

#include <Game/Game.hpp>
#include <Game/Display.hpp>

#include <Math/Matrix4x4.hpp>
#include <Math/Vector4D.hpp>

#include <Entity/TransformComponent.hpp>
#include <Entity/MeshComponent.hpp>
#include <Entity/CameraComponent.hpp>
#include <Entity/LightComponent.hpp>
#include <Entity/TerrainComponent.hpp>

#include <Entity/Entity.hpp>
#include <Math/Rect.hpp>

#include <Input/InputSystem.hpp>
#include <glad/glad.h>

struct alignas(16) LightData
{
	Vector4D color;
	Vector4D direction;
};

struct alignas(16) TerrainData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;// the number of texels along one edge of the height map
	f32 _padding[3]; // padding to complete 16-byte alignment
};

struct alignas(16) UniformData
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4D cameraPosition;
	LightData light;
	TerrainData terrain;
};


// Simple 4x4 matrix implementation
struct Mat4 {
    float m[16];
    
    Mat4() {
        // Initialize to identity matrix
        for (int i = 0; i < 16; i++) {
            m[i] = 0.0f;
        }
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    
    void setIdentity() {
        for (int i = 0; i < 16; i++) {
            m[i] = 0.0f;
        }
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    
    // Matrix multiplication - column-major order
    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[j*4+i] = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result.m[j*4+i] += m[k*4+i] * other.m[j*4+k];
                }
            }
        }
        return result;
    }
};

// Create translation matrix
Mat4 translate(float x, float y, float z) {
    Mat4 result;
    result.m[12] = x;
    result.m[13] = y;
    result.m[14] = z;
    return result;
}

// Create scaling matrix
Mat4 scale(float x, float y, float z) {
    Mat4 result;
    result.m[0] = x;
    result.m[5] = y;
    result.m[10] = z;
    return result;
}

// Create rotation matrix around X axis
Mat4 rotateX(float angle) {
    Mat4 result;
    float c = cos(angle);
    float s = sin(angle);
    result.m[5] = c;
    result.m[6] = s;
    result.m[9] = -s;
    result.m[10] = c;
    return result;
}

// Create rotation matrix around Y axis
Mat4 rotateY(float angle) {
    Mat4 result;
    float c = cos(angle);
    float s = sin(angle);
    result.m[0] = c;
    result.m[2] = -s;
    result.m[8] = s;
    result.m[10] = c;
    return result;
}

// Create rotation matrix around Z axis
Mat4 rotateZ(float angle) {
    Mat4 result;
    float c = cos(angle);
    float s = sin(angle);
    result.m[0] = c;
    result.m[1] = s;
    result.m[4] = -s;
    result.m[5] = c;
    return result;
}

// Create perspective projection matrix
Mat4 perspective(float fov, float aspect, float near, float far) {
    Mat4 result;
    float f = 1.0f / tan(fov / 2.0f);
    
    result.m[0] = f / aspect;
    result.m[5] = f;
    result.m[10] = (far + near) / (near - far);
    result.m[11] = -1.0f;
    result.m[14] = (2.0f * far * near) / (near - far);
    result.m[15] = 0.0f;
    
    return result;
}

// Print matrix (for debugging)
void printMatrix(const Mat4& matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix.m[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


GraphicsEngine::GraphicsEngine ( Game* game ) : m_game ( game )
{
	this->m_render_system = new RenderSystem();
	auto display = game->m_display.get();
	Rect screen_size = display->getScreenSize();
	display->m_swapChain = this->m_render_system->createSwapChain 
	( 
		display->getHandle(), 
		screen_size.width, 
		screen_size.height 
	);
}

void GraphicsEngine::update ( )
{
	auto context = m_render_system->getImmediateDeviceContext ( );

	glEnable(GL_DEPTH_TEST);

	auto swapChain = m_game->m_display->m_swapChain;

	context->clearRenderTargetColor ( swapChain, 0, 0, 0, 1 );
	auto winSize = m_game->m_display->getClientSize ( );
	context->setViewportSize ( winSize.width, winSize.height );

	
	UniformData uniformData = {};

	for (auto c : m_cameras)
	{
		auto t = c->getEntity ( )->getTransform ( );
		uniformData.cameraPosition = t->getPosition ( );
		c->setScreenArea ( winSize );
		c->getViewMatrix ( uniformData.view );
		c->getProjectionMatrix ( uniformData.proj );
	}

    // Use our shader program - already binded
	for (auto m : m_meshes)
	{
		auto transform = m->getEntity ( )->getTransform ( );
		transform->getWorldMatrix ( uniformData.world );
		
		auto mesh = m->getMesh ();
		
		context->setVertexBuffer ( mesh->m_vertex_buffer );
		context->setIndexBuffer ( mesh->m_index_buffer );
		
		const auto materials = m->getMaterials ( );

		for (auto i = 0; i < mesh->getNumMaterialSlots ( ); i++)
		{
			if (i >= materials.size ( )) break;
			auto mat = materials[i].get ( );

			context->setCullMode ( mat->getCullMode ( ) );
			context->setAttributes( mesh->m_attributes );
			
			// uniformData.proj.transpose();
			// uniformData.view.transpose();
			// uniformData.world.transpose();

			//mat->setData ( &uniformData, sizeof ( UniformData ) );
			//context->setUniformBuffer ( mat->m_constant_buffer, 0);

// Define scaling factors
float scaleX = 2.0f;  // Scale 2x on X axis
float scaleY = 2.0f;  // No change on Y axis
float scaleZ = 2.0f;  // Half size on Z axis

// Create scaling matrix
Mat4 scaleMatrix = scale(scaleX, scaleY, scaleZ);

if(this->m_game->getInputSystem()->isKeyDown(Key::W)){
	x += 0.01;
}

// Create translation matrix (moving back 3 units)
Mat4 translateMatrix = translate(0.0f, 0.0f, 0);
//x = 0;
// Apply transformations in order: first scale, then translate
Mat4 modelMatrix = translateMatrix * scaleMatrix;

// Apply projection
Mat4 proj = perspective(1.3f, this->m_game->m_display->m_size.width / this->m_game->m_display->m_size.height, 0.01f, 100.0f);

// Combine everything
Mat4 transform = proj * modelMatrix;



			context->setVertexShader ( mat->m_vertex_shader );
			context->setPixelShader ( mat->m_pixel_shader );

			GLuint transformLoc = glGetUniformLocation(this->getRenderSystem()->m_imm_device_context->m_ShaderProgram.spo, "transform");


			//context->setUniformBuffer(mat->m_constant_buffer, 0);
    		if (transformLoc == -1) {
       	 		std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    		}

			
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.m);
			context->setTexture ( &mat->m_vec_textures[0], (unsigned int)mat->m_vec_textures.size ( ) );

			auto slot = mesh->getMaterialSlot ( i );
			context->drawIndexedTriangleList ( (unsigned int)slot.num_indices, (unsigned int)slot.start_index, 0 );
		}
	}

    this->m_game->m_display->m_swapChain->present(true);
}

RenderSystem* GraphicsEngine::getRenderSystem ( )
{
	return m_render_system;
}

void GraphicsEngine::addComponent ( Component* component )
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.emplace ( c );
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		if (!m_cameras.size ( )) m_cameras.emplace ( c );
	}
	else if (auto c = dynamic_cast<LightComponent*>(component))
	{
		if (!m_lights.size ( )) m_lights.emplace ( c );
	}
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		if (!m_terrains.size ( )) m_terrains.emplace ( c );
	}
}

void GraphicsEngine::removeComponent ( Component* component )
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.erase ( c );
	else if (auto c = dynamic_cast<CameraComponent*>(component))
		m_cameras.erase ( c );
	else if (auto c = dynamic_cast<LightComponent*>(component))
		m_lights.erase ( c );
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		m_terrains.erase ( c );
	}
}

GraphicsEngine::~GraphicsEngine ( )
{
	delete this->m_render_system;
}