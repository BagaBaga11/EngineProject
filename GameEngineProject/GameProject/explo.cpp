#include "explo.h"
#include <iostream>

Explo::Explo(Level* mylevel) : Sprite(mylevel)
{
	SetBMP("graphics/explode64.bmp", 5, 2, 2);
	animationManager.AddAnimation("Wall", { 0,1,2,3,4,5,6,7,8,9 }, 0.1f);
	animationManager.SetCurrentAnimation("Wall");
}

Explo::~Explo()
{
}

void Explo::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
	if (animationManager.GetCurrentFrame() == 9)
	{	
		delete this;
	}
}
