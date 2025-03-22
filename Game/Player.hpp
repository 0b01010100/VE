#pragma once
#include <All.hpp>

class Player : public Entity
{
public:
	Player ( );
	virtual ~Player ( );

protected:
	virtual void onCreate ( ) override;
	virtual void onUpdate ( f32 deltaTime ) override;

private:
	Entity* m_entity = nullptr;

	f32 m_elapsedSeconds = 0.0f;

	f32 m_forward = 0.0f;
	f32 m_rightward = 0.0f;
};
