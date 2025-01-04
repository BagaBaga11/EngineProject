#include "Missile.h"
#include "Player.h"

#include <iostream>

Player::Player(Level* mylevel):Pawn(mylevel)
{
	SetBMP("graphics/Ship2.bmp", 7, 3, 64);
	SetStartPos(240.0f, 320.0f);
	SetGravScale(0.0f);
	SetSpeed(200.0f);
	SetSensor(true);

	animationManager.AddAnimation("idle", { 4 }, 1.0f);
	animationManager.AddAnimation("Damage", { 4,18 }, 1.0f);
	animationManager.AddAnimation("tleft", { 3,2,1 }, 0.1f);
	animationManager.AddAnimation("tright", { 5,6,7 }, 0.1f);
	animationManager.SetCurrentAnimation("idle");
	StartObject();
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
	timeinv += delta;
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
			if (timeinv > 2)
			{
				healt = healt--;
				timeinv = 0;
				std::cout << healt;
			}
		
	animationManager.SetCurrentAnimation("Damage");
}

bool Player::GetAlive()
{
	return alive;
}

void Player::Fire()
{
	if (timedelta > 1)
	{
		Missile* missile = new Missile(mylevel);
		missile->SetBMP("graphics/hmissile.bmp", 4, 4, 32);
		missile->SetStartPos(newposX + 17.0f, newposY - 50.0f);
		missile->SetGravScale(-100.0f);
		missile->SetSensor(true);
		missile->StartObject();
		timedelta = 0.0f;
	}

}
