#pragma once
#include <GameObjects.h>
#include "GameEngineProject.h"
class Companion : public GameObject
{
public:
	Companion(Level* mylevel, GameEngine engine);
	~Companion();
	void Update(float deltaTime)override;

	void Up(float movespeed);
	void Down(float movespeed);
	void Left(float movespeed);
	void Right(float movespeed);
	void Fire();

	bool Getbool();

	void Hit() override;
	void ChangeMissile();
	void ChangeHealth(int health);
	void Attach();
private:
	bool pickedUp;
	float missileTime;
	float time;
	float delta;
	float timeinv;
	int healt;
};

