#include "FriendlyMissile.h"

FriendlyMissile::FriendlyMissile(Level* mylevel) : Missile(mylevel)
{
	SetBMP("graphics/missile.bmp", 2, 3, 2);
	animationManager.AddAnimation("One", { 1,2 }, 0.1f);
	animationManager.AddAnimation("Two", { 3,4 }, 0.1f);
	animationManager.AddAnimation("Three", { 5,6 }, 0.1f);
	SetSensor(true);
}

FriendlyMissile::~FriendlyMissile()
{
}
