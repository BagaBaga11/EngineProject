#include "Missile.h"
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
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("idle"))
	{
		animationManager.SetCurrentAnimation("idle");
	}
	newposY -= moveSpeed * delta;
	if (newposY < 0)
	{
		newposY = 0;
	}
}

void Player::Left()
{
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("tleft"))
	{
		animationManager.SetCurrentAnimation("tleft");
		animationManager.SetStopFrame(2);
	}
	newposX -= moveSpeed * delta;	
	if (newposX < 0)
	{
		newposX = 0;
	}
}

void Player::Right()
{	
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("tright"))
	{
		animationManager.SetCurrentAnimation("tright");
		animationManager.SetStopFrame(2);
	}
	newposX += moveSpeed * delta;
	if (newposX > 418)
	{
		newposX = 418;
	}
}

void Player::Down()
{
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("idle"))
	{
		animationManager.SetCurrentAnimation("idle");
	}
	newposY += moveSpeed * delta;
	if (newposY > 578)
	{
		newposY = 578;
	}
}

void Player::Update(float deltaTime)
{
	delta = deltaTime;
	timedelta += deltaTime;
	Pawn::Update(deltaTime);
}

void Player::RemDown()
{
}

void Player::RemUp()
{
}

void Player::RemRight()
{
	animationManager.SetCurrentAnimation("idle");
}

void Player::RemLeft()
{
	animationManager.SetCurrentAnimation("idle");
}

void Player::SetSpeed(float speed)
{
	moveSpeed = speed;
}

void Player::Hit()
{
	if (healt <= 0)
	{
		alive = false;
	}
	else
	{
		healt = healt--;
	}		
}

bool Player::GetAlive()
{
	return alive;
}

void Player::Fire()
{
	if (timedelta > 2)
	{
		Missile* missile = new Missile(mylevel);
		missile->SetBMP("graphics/hmissile.bmp", 4, 4, 32);
		missile->SetStartPos(newposX + 17.0f, newposY - 40.0f);
		missile->SetGravScale(-100.0f);
		missile->SetSensor(true);
		//missile->SetFilter(2);
		missile->StartObject();
		timedelta = 0.0f;
	}

}
