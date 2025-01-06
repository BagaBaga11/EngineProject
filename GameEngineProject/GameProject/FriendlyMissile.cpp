#include "FriendlyMissile.h"

FriendlyMissile::FriendlyMissile(Level* mylevel) : Missile(mylevel)
{
	SetBMP("graphics/hmissile.bmp", 4, 4, 32);
	SetGravScale(-100.0f);
	SetSensor(true);
	StartObject();
}

FriendlyMissile::~FriendlyMissile()
{
}
