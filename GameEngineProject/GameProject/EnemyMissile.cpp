#include "EnemyMissile.h"

EnemyMissile::EnemyMissile(Level* mylevel) : Missile(mylevel)
{
	SetBMP("graphics/EnWeap6.bmp", 8, 1, 32);
	SetGravScale(100.0f);
	SetSensor(true);
	animationManager.AddAnimation("Project", { 0,1,2,3,4,5,6,7 }, 0.1f);
	animationManager.SetCurrentAnimation("Project");
	StartObject();
}

EnemyMissile::~EnemyMissile()
{
}
