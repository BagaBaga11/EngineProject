#pragma once
#include "Asteroids.h"
#include "GameEngineProject.h"

class MetalAsteroids :public Asteroids
{
public:
	MetalAsteroids(Level* mylevel, GameEngine engine);
	~MetalAsteroids();

	void Update(float deltaTime) override;
	void Hit() override;

private:
	GameEngine Engine;
};

