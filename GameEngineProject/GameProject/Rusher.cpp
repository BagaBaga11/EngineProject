#include "Rusher.h"

Rusher::Rusher(Level* mylevel, GameEngine engine) : GameObject(mylevel)
{
	SetBMP("graphics/rusher.bmp", 4, 6, 32);
	float value = engine.getRandomFloat(0, 460);
	bool ver = engine.RandomBool();
	float val;
	if (ver)
	{
		val = -100;
	}
	else
	{
		val = 580;
	}
	SetStartPos(val,value);
	SetGravScale(5.0f);
	SetSensor(false);
	animationManager.AddAnimation("Rusher", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, 0.1f);
	animationManager.SetCurrentAnimation("Rusher");
	StartObject();
}
Rusher::~Rusher()
{
}
