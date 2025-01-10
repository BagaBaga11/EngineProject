#include "Companion.h"
#include "FriendlyMissile.h"

Companion::Companion(Level* mylevel, GameEngine engine) : GameObject(mylevel)
{
	SetBMP("graphics/clone.bmp", 4, 5, 2);
	float value = engine.getRandomFloat(0, 460);
	SetStartPos(value, -100.0f);
	SetGravScale(10.0f);
	SetSensor(true);
	animationManager.AddAnimation("Default", { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, 0.1f);
	animationManager.AddAnimation("Damage", { 17,18,19,20 }, 0.1f);
	animationManager.SetCurrentAnimation("Default");
}

Companion::~Companion()
{
}

void Companion::Update(float deltaTime)
{
	timeinv += deltaTime;
	delta = deltaTime;
	time += deltaTime;
	if (!pickedUp)
	{
		GetPosition();
		SetPos(Firstpos, Secondpos, 0);
	}
	GameObject::Update(deltaTime);
}

void Companion::ChangeMissile()
{
	if (missileTime > 0)
	{
		missileTime += 10;
	}
	else
	{
		missileTime = 10;
	}
}

void Companion::Up(float movespeed)
{
	Secondpos -= movespeed * delta * 320;
	t->AddPosition(0, movespeed * delta, 0);
}

void Companion::Down(float movespeed)
{
	Secondpos += movespeed * delta * 320;
	t->AddPosition(0, -(movespeed * delta), 0);
}

void Companion::Left(float movespeed)
{
	Firstpos -= movespeed * delta * 240;
	t->AddPosition(-(movespeed * delta), 0, 0);
}

void Companion::Right(float movespeed)
{
	Firstpos += movespeed * delta * 240;
	t->AddPosition(movespeed * delta, 0, 0);
}

void Companion::Fire()
{
	FriendlyMissile* missile = new FriendlyMissile(mylevel);
	missile->SetStartPos(Firstpos, Secondpos - 50.0f);
	if (missileTime > 10)
	{
		missile->animationManager.SetCurrentAnimation("Three");
		missile->SetGravScale(-400.0f);
	}
	else if (missileTime > 0)
	{
		missile->animationManager.SetCurrentAnimation("Two");
		missile->SetGravScale(-200.0f);
	}
	else
	{
		missile->animationManager.SetCurrentAnimation("One");
		missile->SetGravScale(-100.0f);
	}
	missile->StartObject();
	time = 0.0f;
}

bool Companion::Getbool()
{
	return pickedUp;
}

void Companion::Hit()
{
	if (timeinv > 2)
	{
		healt = healt--;
		timeinv = 0;
		animationManager.SetCurrentAnimation("Damage");
	}
	if (healt <= 0)
	{
		delete this;
	}
}

void Companion::ChangeHealth(int health)
{
	healt += health;
	if (healt > 3)
	{
		healt = 3;
	}
}

void Companion::Attach()
{	
	pickedUp = true;
	float y = mylevel->GetPawn()->GetXPos();
	float x = mylevel->GetPawn()->GetYPos();
	SetContainerPosition(x - 20 ,y - 10);
	float w = mylevel->GetPawn()->GetCollisionX();
	float h = mylevel->GetPawn()->GetCollisionX();
	SetPos(w+30 , h-60,0);
}
