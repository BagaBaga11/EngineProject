#include "Sprite.h"
#include "SDL.h"
Sprite::Sprite()
{
}
Sprite::~Sprite()
{
}

void Sprite::SetBMP(std::string image, int wSec, int hSec, int objsize)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    myBMP = image;
    widthSection = wSec;
    heightSection = hSec;
    objSize = objsize;
}

void Sprite::Update(float deltaTime)
{
}
