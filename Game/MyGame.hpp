#pragma once
#include <Game/Game.hpp>

class MyGame : public Game
{
public:
	MyGame();
	~MyGame();
protected:
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;


private:
	Entity* m_entity = nullptr;

	float m_rotation = 0.0f;

	bool m_looked = true;
};
