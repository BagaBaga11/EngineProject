#pragma once
#include "GameObjects.h"
#include <iostream>
#include "GameEngineProject.h"
#include <vector>
#include "Levels.h"

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
	virtual void RemRight();
	virtual void RemLeft();
	virtual void RemUp();
	virtual void RemDown();
	virtual void Fire();

	virtual void UpdateObject(float deltaTime) override;
private:
	const uint8_t* keyState;
	bool pessLeft = false;
	bool pessRight = false;
	bool pessUp = false;
	bool pessDown = false;
};

