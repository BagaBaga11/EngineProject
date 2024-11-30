#pragma once
#include "Pawns.h"
class Player : public Pawn
{
public:
	Player(Level* mylevel);
	~Player();
	 void Up() override;
	 void Left() override;
	 void Right() override;
	 void Down() override;
	 virtual void UpdateObject(float deltaTime) override;

	 void SetSpeed(float speed);
protected:
	float delta = 0.0f;
	float moveSpeed  = 0.0f;
};

