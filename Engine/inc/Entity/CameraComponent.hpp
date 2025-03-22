#pragma once
#include <Prerequisites.hpp>
#include <Entity/Component.hpp>
#include <Math/Rect.hpp>
#include <Math/Matrix4x4.hpp> 

class CameraComponent : public Component
{
public:
	CameraComponent ( );
	virtual ~CameraComponent ( ) override;

	void getViewMatrix ( Matrix4x4& view );

	void getProjectionMatrix ( Matrix4x4& proj );


	void setFarPlane ( f32 farPlane );
	f32 getFarPlane ( );

	void setNearPlane ( f32 nearPlane );
	f32 getNearPlane ( );

	void setFieldOfView ( f32 fieldOfView  );
	f32 getFieldOfView (  );

	void setType ( const CameraType& type );
	CameraType getType ( );

	void setScreenArea ( const Rect& area );
	Rect getScreenArea ( );

private:
	void computeProjectionMatrix ( );
protected:
	virtual void onCreateInternal ( ) override;
private:
	Matrix4x4 m_projection;

	f32 m_nearPlane = 0.01f;
	f32 m_farPlane = 100.0f; 
	f32 m_fieldOfView = 1.3f;
	CameraType m_type = CameraType::Perspective;
	Rect m_screenArea;


};
