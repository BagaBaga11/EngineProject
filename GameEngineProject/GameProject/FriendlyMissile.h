#pragma once
#include "Missile.h"
class FriendlyMissile : public Missile
{
public:
	FriendlyMissile(Level* mylevel);
	~FriendlyMissile();
};

