#pragma once
#include "Asteroids.h"
#include "GameEngineProject.h"

enum AsteroidType
{
	MainAsteroid,
	RightAsteroid,
	LeftAsteroid
};

class StoneAsteroids : public Asteroids
{
	AsteroidType asteroidType;
public:
	StoneAsteroids(Level* mylevel, GameEngine engine);
	~StoneAsteroids();

	void Update(float deltaTime) override;
	void Hit() override;
	void Setoffset(float off);
	void SetDestruction(bool spawnasteroids);

private:
	float Offset = 0.0f;
	bool Spawnasteroids = false;

	GameEngine Engine;
};

