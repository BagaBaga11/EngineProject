#pragma once
#include <Levels.h>
class XenonLevel : public Level
{
public:
	void Contact(GameObject* A, GameObject* B)override;
};

