#pragma once
#include <string>
#include <memory>
#include "Animation.h"

class Level;
class Animation;

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

    void SetStartPos(float x, float y);

    void Draw();

    void SetPos(float x, float y, float z);
    void SetSca(float x, float y, float z);
    void SetRot(float angle, float x, float y, float z);

    Animation animationManager;
protected:

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
    float centerX;
    float centerY;
        Transform* t;
};

