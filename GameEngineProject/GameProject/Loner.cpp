#include "Loner.h"
#include "GameEngineProject.h"
#include "Missile.h"

Loner::Loner(Level* mylevel, GameEngine engine) : GameObject(mylevel)
{
   SetBMP("graphics/LonerA.bmp", 4, 4, 32);
   float value = engine.getRandomFloat(0, 460);
   vertical = engine.RandomBool();
   float val;
   float Grav;
   if (vertical)
   {
	   val = -50;
	   Grav = 10.0f;
   }
   else
   {
	   val = 480;
	   Grav = -10.0f;
   }
   SetStartPos(value, val);
   SetGravScale(Grav);
   SetSensor(false);
   animationManager.AddAnimation("Loner", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
   animationManager.SetCurrentAnimation("Loner");
   StartObject();
}
Loner::~Loner()
{

}

void Loner::Update(float deltaTime)
{	
	GameObject::Update(deltaTime);
	GetPosition();
	SetPos(Secondpos, Firstpos, 0);
	if (Secondpos > 510 || Secondpos < -100 )
	{
		Hit();
	}
	time += deltaTime;
	if (time > 2)
	{
		Missile* missile = new Missile(mylevel);
		missile->SetBMP("graphics/EnWeap6.bmp", 8, 1, 32);
		missile->SetStartPos(Secondpos + 17.0f, Firstpos + 40.0f);
		missile->SetGravScale(100.0f);
		missile->SetSensor(true);
		missile->animationManager.AddAnimation("Project", { 0,1,2,3,4,5,6,7 }, 0.1f);
		missile->animationManager.SetCurrentAnimation("Project");
		SDL_Point pivot = { objSize/2,  objSize / 2 };
		missile->StartObject();
		time = 0.0f;
	}
}

void Loner::Hit()
{
	delete this;
}

