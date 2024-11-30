#include "Player.h"
#include <iostream>

Player::Player(Level* mylevel):Pawn(mylevel)
{
}

Player::~Player()
{
}

void Player::Up()
{
	newposY -= moveSpeed * delta;
}

void Player::Left()
{
	if (animationManager.GetAnimation() != "tleft")
	{
		animationManager.SetCurrentAnimation("tleft");
	}
	newposX -= moveSpeed * delta;	
}

void Player::Right()
{	
	animationManager.SetCurrentAnimation("tright");
	newposX += moveSpeed * delta;
}

void Player::Down()
{
	newposY += moveSpeed * delta;
}

void Player::UpdateObject(float deltaTime)
{
	delta = deltaTime;
	Pawn::UpdateObject(deltaTime);
}

void Player::SetSpeed(float speed)
{
	moveSpeed = speed;
}
