#pragma once
#include <GameObjects.h>
#include "GameEngineProject.h"
#include "explo.h"

class Missile : public GameObject
{
public:
	Missile(Level* mylevel);
	~Missile();

	void Update(float deltaTime) override;
	void Hit()override;
protected:
	float mytimer;
};

