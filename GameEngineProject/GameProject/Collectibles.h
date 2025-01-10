#pragma once
#include <GameObjects.h>
class Collectibles : public GameObject
{
public:
	Collectibles(Level* mylevel);
	~Collectibles();
	virtual void Upgrade(GameObject* Up);
};

