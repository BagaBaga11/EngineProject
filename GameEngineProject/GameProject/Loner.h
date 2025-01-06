#pragma once
#include "Enemy.h"
#include "GameEngineProject.h"
#include "explo.h"

class Loner : public Enemy
{
public:
	Loner(Level* mylevel,GameEngine engine);
	~Loner();

	void Update(float deltaTime) override;
	void Hit() override;
protected :
	float time = 0;
};

