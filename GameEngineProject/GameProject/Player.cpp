#include "FriendlyMissile.h"
#include "Player.h"

#include <iostream>

Player::Player(Level* mylevel) :Pawn(mylevel)
{
	SetBMP("graphics/Ship2.bmp", 7, 3, 64);
	SetStartPos(240, 320);
	SetGravScale(0.0f);
	SetSpeed(1.0f);
	SetSensor(true);

	animationManager.AddAnimation("idle", { 4 }, 1.0f);
	animationManager.AddAnimation("Damage", { 4,18 }, 1.0f);
	animationManager.AddAnimation("tleft", { 3,2,1 }, 0.1f);
	animationManager.AddAnimation("tright", { 5,6,7 }, 0.1f);
	animationManager.SetCurrentAnimation("idle");
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
	if (Secondpos >= 10)
	{
		Secondpos -= moveSpeed * delta * 320;
		t->AddPosition(0, moveSpeed * delta, 0);
	}
}

void Player::Left()
{
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("tleft"))
	{
		animationManager.SetCurrentAnimation("tleft");
		animationManager.SetStopFrame(2);
	}
	if (Firstpos >= 10)
	{
		Firstpos -= moveSpeed * delta * 240;
		t->AddPosition(-(moveSpeed * delta), 0, 0);
	}
}

void Player::Right()
{
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("tright"))
	{
		animationManager.SetCurrentAnimation("tright");
		animationManager.SetStopFrame(2);
	}
	if (Firstpos <= 460.0f)
	{
		Firstpos += moveSpeed * delta * 240;
		t->AddPosition(moveSpeed * delta, 0, 0);
	}
}

void Player::Down()
{
	if (animationManager.GetAnimation("") != animationManager.GetAnimation("idle"))
	{
		animationManager.SetCurrentAnimation("idle");
	}
	if (Secondpos <= 635.0f)
	{
		std::cout << Secondpos << std::endl;
		Secondpos += moveSpeed * delta * 320;
		t->AddPosition(0, -(moveSpeed * delta), 0);
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
	if (timeinv > 2)
	{
		healt = healt--;
		timeinv = 0;
	}

	animationManager.SetCurrentAnimation("Damage");

	if (healt <= 0)
	{
		delete this;
	}
}

bool Player::GetAlive()
{
	return alive;
}

void Player::Fire()
{
	if (timedelta > 1)
	{
		FriendlyMissile* missile = new FriendlyMissile(mylevel);
		missile->SetStartPos(Firstpos + 17.0f, Secondpos - 50.0f);
		missile->StartObject();
		timedelta = 0.0f;
	}

}
