#include "Loner.h"
#include "GameEngineProject.h"
#include "Missile.h"

Loner::Loner(Level* mylevel, GameEngine engine) : GameObject(mylevel)
{
   SetBMP("graphics/LonerC.bmp", 4, 4, 32);
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
	GetPosition();
	newposX = Secondpos;
	newposY = Firstpos;	
	GameObject::Update(deltaTime);
	if (newposX > 510 || newposX < -100 )
	{
		Hit();
	}
	time += deltaTime;
	if (time > 2)
	{
		Missile* missile = new Missile(mylevel);
		missile->SetBMP("graphics/EnWeap6.bmp", 8, 1, 32);
		missile->SetStartPos(newposX + 17.0f, newposY + 40.0f);
		missile->SetGravScale(100.0f);
		missile->SetSensor(true);
		missile->animationManager.AddAnimation("Project", { 0,1,2,3,4,5,6,7 }, 0.1f);
		missile->animationManager.SetCurrentAnimation("Project");
		SDL_Point pivot = { objSize/2,  objSize / 2 };
		missile->StartObject();
		time = 0.0f;
	}
}

