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


    objRect = nullptr;

    objPosition = nullptr;

        auto itObject = std::find(mylevel->everyArray.begin(), mylevel->everyArray.end(), this);

        if (itObject != mylevel->everyArray.end())
        {
            size_t index = std::distance(mylevel->everyArray.begin(), itObject);
            mylevel->everyArray.erase(itObject);

            if (index < mylevel->bmpArray.size())
            {
                mylevel->bmpArray.erase(mylevel->bmpArray.begin() + index);
            }
        } 
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

void Sprite::SetStartPos(float x, float y)
{
    newposX = x;
    newposY = y;
}

void Sprite::SetRotation(double angle,SDL_Point pivot)
{
    rotationAngle = angle;
    rotationPivot = new SDL_Point(pivot);
}

SDL_Point* Sprite::GetPivot()
{
    if (rotationPivot)
    {
         return rotationPivot;
    }
    return 0;
}

double Sprite::GetAngle()
{
    return rotationAngle;
}
