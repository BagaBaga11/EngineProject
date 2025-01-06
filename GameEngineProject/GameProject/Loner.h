#pragma once
#include <GameObjects.h>
#include "GameEngineProject.h"
#include "explo.h"

class Loner : public GameObject
{
public:
	Loner(Level* mylevel,GameEngine engine);
	~Loner();

	void Update(float deltaTime) override;
	void Hit() override;
protected :
	float time = 0;
};

