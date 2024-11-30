#pragma once
#include "GameObjects.h"
#include <iostream>
#include "GameEngineProject.h"
#include <vector>
#include "Levels.h"
#include "GameObjects.h"

class Pawn :public GameObject
{
public:
	Pawn(Level* mylevel);
	virtual ~Pawn();

	void CheckKeyboard();
	virtual void Right();
	virtual void Left();
	virtual void Up();
	virtual void Down();

	virtual void UpdateObject(float deltaTime) override;

private:
	const uint8_t* keyState;
};

