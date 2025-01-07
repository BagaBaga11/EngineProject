#include "Wall.h"

Wall::Wall(Level* mylevel):GameObject(mylevel)
{
	SetGravScale(0.0f);
	SetSensor(true);
}

Wall::~Wall()
{

}

void Wall::Update(float deltaTime)
{
	Firstpos = newposX;
	Secondpos = newposY;
}

