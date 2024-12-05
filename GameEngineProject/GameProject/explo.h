#pragma once
#include <Sprite.h>
class Explo :
    public Sprite
{
public:
    Explo(Level* mylevel);
    ~Explo();
    void Update(float deltaTime)override;
};

