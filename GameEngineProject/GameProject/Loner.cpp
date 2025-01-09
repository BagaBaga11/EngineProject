#include "Loner.h"
#include "GameEngineProject.h"
#include "EnemyMissile.h"

Loner::Loner(Level* mylevel, GameEngine engine) : Enemy(mylevel)
{
   SetBMP("graphics/LonerA.bmp", 4, 4, 4);
   float value = engine.getRandomFloat(0, 460);
   vertical = engine.RandomBool();
   float val;
   if (vertical)
   {
	   val = -50;
	   grav = 10.0f;
   }
   else
   {
	   val = 480;
	   grav = -10.0f;
   }
   SetStartPos(val, value);
   SetGravScale(0);
   SetSensor(false);
   animationManager.AddAnimation("Loner", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
   animationManager.SetCurrentAnimation("Loner");
}
Loner::~Loner()
{

}

void Loner::Update(float deltaTime)
{	
	GameObject::Update(deltaTime);
	ApplyForce(grav * 400,0 ,deltaTime);
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	if (Secondpos > 600 || Secondpos < -100 )
	{
		Hit();
	}
	time += deltaTime;
	if (time > 3)
	{
		EnemyMissile* missile = new EnemyMissile(mylevel);
		missile->SetStartPos(Firstpos + 17.0f, Secondpos + 40.0f);
		missile->StartObject();
		time = 0.0f;
	}
}

void Loner::Hit()
{
	delete this;
}

