#include "FriendlyMissile.h"

FriendlyMissile::FriendlyMissile(Level* mylevel) : Missile(mylevel)
{
	SetBMP("graphics/missile.bmp", 2, 6, 2);
	animationManager.AddAnimation("One", { 1,2 }, 0.1f);
	SetGravScale(-200.0f);
	SetSensor(true);
}

FriendlyMissile::~FriendlyMissile()
{
}
