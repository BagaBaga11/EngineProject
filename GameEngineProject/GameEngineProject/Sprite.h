#pragma once
#include <string>
#include <memory>
#include "Animation.h"

class Level;
class SDL_Rect;
class SDL_Texture;
class Animation;
class SDL_Point;
typedef unsigned int GLuint;

class Transform {
public:
    Transform();
    ~Transform();
    void SetPosition(float x, float y, float z);
    void SetScale(float x, float y, float z);
    void SetRotation(float angle, float x, float y, float z);

    void Draw();
    void Start();
    void SetTexture(const char* image, float Ncol, float Nlin, float size);
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

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
    void SetStartPos(float x, float y);

    void SetRotation(double angle, SDL_Point pivot);
    void Draw();

    SDL_Point* GetPivot();
    double GetAngle();

    Animation animationManager;
protected:
    SDL_Rect* objRect = nullptr;
    SDL_Rect* objPosition = nullptr;

    Level* mylevel;

     SDL_Point* rotationPivot;
    double rotationAngle = 0.0;
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
    float centerX;
        float centerY;
        Transform* t;
};

