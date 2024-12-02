#include "GameObjects.h"
#include "Levels.h"
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Animation.h"


/*Cat GameObject::Select(int Choice)
{
    switch (Choice)
    { 
    case 1:
        return Cat::Players;
    case 2:
        return Cat::Missiles;
    case 3:
        return Cat::Enemys;
    }
}
void GameObject::SetFilter(int choice)
{
    myfilter = choice;
}*/
GameObject::GameObject(Level* mylevel) : mylevel(mylevel)
{
    if (mylevel != nullptr)
    {
        mylevel->objectArray.push_back(this);
    }
}

GameObject::~GameObject()
{
    delete(SID);
    delete objRect;
    delete objPosition;
    if (mylevel != nullptr && !mylevel->objectArray.empty()) 
    {
        auto itObject = std::find(mylevel->objectArray.begin(), mylevel->objectArray.end(), this);

        if (itObject != mylevel->objectArray.end())
        {
            size_t index = std::distance(mylevel->objectArray.begin(), itObject);
            mylevel->objectArray.erase(itObject);

            if (index < mylevel->bmpArray.size()) 
            {
                mylevel->bmpArray.erase(mylevel->bmpArray.begin() + index);
            }
        }
    }
}

void GameObject::UpdateObject(float deltaTime)
{
    if (myBMP != "0" && mylevel->GiveRender() != nullptr && objRect == nullptr)
    {
        texture = LoadTexture(myBMP, mylevel->GiveRender());
        SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
        mylevel->bmpArray.push_back(texture);
        if (widthSection != 0 && heightSection != 0)
        {
            frameWidth = textureWidth / widthSection;
            frameHeight = textureHeight / heightSection;
        }
        objRect = SetRect(0, 0, frameWidth, frameHeight);
    }

    objPosition = SetRect(newposX, newposY, objSize, objSize);

    animationManager.Update(deltaTime);

    int frameIndex = animationManager.GetCurrentFrame();
    objRect->x = (frameIndex % widthSection) * frameWidth;
    objRect->y = (frameIndex / widthSection) * frameHeight;
}

void GameObject::SetBMP(std::string image, int wSec, int hSec, int objsize)
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
void GameObject::StartObject()
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = GetGravScale();
    bodyDef.position = b2Vec2{ newposX,newposY };
    bodyDef.isBullet = missil;
    b2BodyId* body = new b2BodyId(b2CreateBody(*mylevel->GetWorld(), &bodyDef));
    bodyID = body;
    b2Polygon dynamicBox = b2MakeBox(objSize/4, objSize/4);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    shapeDef.enableContactEvents = true;
   /* shapeDef.filter.categoryBits = Select(myfilter);
   switch (myfilter)
    {
    case 1:
        shapeDef.filter.maskBits = Cat::Missiles;
    case 2:
        shapeDef.filter.maskBits = Cat::Players;
    case 3:
        shapeDef.filter.maskBits = Cat::Missiles | Cat::Players | Cat::Walls;
    }*/ 
    SID = new b2ShapeId(b2CreatePolygonShape(*bodyID, &shapeDef, &dynamicBox));
}
std::string GameObject::GetBMP()
{
    return myBMP;
}
SDL_Rect* GameObject::SetRect(int x, int y, int w, int h)
{
    SDL_Rect* rect = new SDL_Rect;

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}

SDL_Texture* GameObject::GetTexture()
{
    return texture;
}

b2BodyId* GameObject::Getbody()
{
    return bodyID;
}


void GameObject::SetStartPos(float x, float y)
{
    newposX = x;
    newposY = y;
}

void GameObject::SetGravScale(float scale)
{
    scaleGrav = scale;
}

float GameObject::GetGravScale()
{
    return scaleGrav;
}

void GameObject::SetSensor(bool bullet)
{
    missil = bullet;
}

void GameObject::Hit()
{
    delete(this);
}

b2ShapeId* GameObject::GetShape()
{
    return SID;
}
