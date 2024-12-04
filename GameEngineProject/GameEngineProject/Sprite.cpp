#include "Sprite.h"
#include "SDL.h"
#include "GameEngineProject.h"
#include "Levels.h"

Sprite::Sprite(Level* mylevel) : mylevel(mylevel)
{
    if (mylevel) {
        mylevel->everyArray.push_back(this);
    }
}
Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    delete objRect;
    delete objPosition;
}

void Sprite::SetBMP(const std::string& image, int wSec, int hSec, int objsize)
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    myBMP = image;
    widthSection = wSec;
    heightSection = hSec;
    objSize = objsize;
}

void Sprite::Update(float deltaTime)
{
    objPosition->x = newposX;
    objPosition->y = newposY;
    objPosition->h = objSize;
    objPosition->w = objSize;
    animationManager.Update(deltaTime);

    int frameIndex = animationManager.GetCurrentFrame();
    objRect->x = (frameIndex % widthSection) * frameWidth;
    objRect->y = (frameIndex / widthSection) * frameHeight;
}

void Sprite::StartObject()
{
    texture = LoadTexture(myBMP, mylevel->GiveRender());
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    if (widthSection != 0 && heightSection != 0) {
        frameWidth = textureWidth / widthSection;
        frameHeight = textureHeight / heightSection;
    }
    objRect = new SDL_Rect{ 0, 0, frameWidth, frameHeight };
    objPosition = new SDL_Rect;
    mylevel->bmpArray.push_back(texture);
}

SDL_Rect* Sprite::GetRect() const
{
    return objRect;
}
