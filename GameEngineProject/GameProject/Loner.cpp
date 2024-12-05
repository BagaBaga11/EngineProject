#include "Loner.h"
#include "GameEngineProject.h"

Loner::Loner(Level* mylevel, GameEngine engine) : GameObject(mylevel)
{
   SetBMP("graphics/LonerC.bmp", 4, 4, 32);
   float value = engine.getRandomFloat(0, 460);
   SetStartPos(value, -100.0f);
   SetGravScale(10.0f);
   SetSensor(false);
   animationManager.AddAnimation("Loner", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
   animationManager.SetCurrentAnimation("Loner");
   StartObject();
}
Loner::~Loner()
{

}

