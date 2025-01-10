#pragma once
#include "Pawns.h"
#include "Missile.h"
#include "Companion.h"
class Player : public Pawn
{
public:
	Player(Level* mylevel);
	~Player();
	 void Up() override;
	 void Left() override;
	 void Right() override;
	 void Down() override;
	 virtual void Update(float deltaTime) override;
	 void RemDown() override;
	 void RemUp() override;
	 void RemRight() override;
	 void RemLeft() override;
	 void Fire() override;

	 void SetSpeed(float speed);
	 void Hit() override;
	 bool GetAlive();
	 void ChangeHealh(int diffhealth);
	 void ChangeMissile();

	 int GetHealth();
	 void SetComp(Companion* Comp);
	 Companion* GetComp();
protected:
	float delta = 0.0f;
	float moveSpeed  = 0.0f;
	int healt = 3;
	float timedelta = 0.0f;
	bool alive = true;
	float timeinv;
	float missileTime;
	Companion* myComp;
};

