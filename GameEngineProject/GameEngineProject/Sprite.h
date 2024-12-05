#pragma once
#include <string>
#include "Animation.h"

class Level;
class SDL_Rect;
class SDL_Texture;
class Animation;
class Sprite
{
public:
    Sprite(Level* mylevel);
    virtual ~Sprite();

    void SetBMP(const std::string& image, int wSec, int hSec, int objsize);
    virtual void Update(float deltaTime);
    virtual void StartObject();

    SDL_Rect* GetRect() const;
    SDL_Rect* GetPosition() const { return objPosition; }
    SDL_Texture* GetTexture() const { return texture; }
    void SetStartPos(float x, float y);

    Animation animationManager;
protected:
    SDL_Texture* texture = nullptr;
    SDL_Rect* objRect = nullptr;
    SDL_Rect* objPosition = nullptr;

    Level* mylevel;

    int textureWidth = 0;
    int textureHeight = 0;
    int frameWidth = 0;
    int frameHeight = 0;
    int widthSection = 0;
    int heightSection = 0;
    int objSize = 0;
    float newposX = 0.0f;
    float newposY = 0.0f;
    std::string myBMP;
    bool isSprite = false;
};

