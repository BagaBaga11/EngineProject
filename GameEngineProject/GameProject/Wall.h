#pragma once
#include <GameObjects.h>
class Wall : public GameObject
{
public:
	Wall(Level* mylevel);
	~Wall();

	void Update(float deltaTime) override;
};

