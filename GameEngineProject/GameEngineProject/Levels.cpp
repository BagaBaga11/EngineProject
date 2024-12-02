#include "Levels.h"
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include "GameObjects.h"
#include <vector>

Level::Level()
{
}

Level::~Level()
{
}

void Level::SetBackground(std::string image)
{
    background = image;
}

const std::string Level::GetBackground()
{
    return background;
}

void Level::Update(float deltaTime)
{
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(*GetWorld(), timeStep, subStepCount);

    b2ContactEvents sensorEvents = b2World_GetContactEvents(*GetWorld());
    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {
        b2ContactBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
        for (size_t t = 0; t < objectArray.size(); t++)
        {
           if (objectArray[t]->GetShape()->index1 == beginTouch->shapeIdA.index1)
           {
               objectArray[t]->Hit();
           }
           if (objectArray[t]->GetShape()->index1 == beginTouch->shapeIdB.index1)
           {
               objectArray[t]->Hit();
           }
        }


    }

    for (size_t i = 0; i < objectArray.size(); ++i)
    {
        if (objectArray[i]->GetGravScale() != 0.0f)
        {
            b2BodyId bod = *objectArray[i]->Getbody();
            b2Vec2 position = b2Body_GetPosition(bod);
            objectArray[i]->newposX = position.x;
            objectArray[i]->newposY = position.y;
        }

        objectArray[i]->UpdateObject(deltaTime);

    }
}


SDL_Renderer* Level::GiveRender()
{
    return renderL;
}

void Level::SetRender(SDL_Renderer* rnd)
{
    renderL = rnd;
}

void Level::SetWorld(b2WorldId* world)
{
    worldID = world;
}

b2WorldId* Level::GetWorld() const
{
    return worldID;
}

void Level::SetGrav(float horizontal, float vertical)
{
    verticalGrav = vertical;
    horizontalGrav = horizontal;
}

float Level::GetGrav(const char* initial)
{
    if (initial == "h")
    {
        return horizontalGrav;
    }
    else if (initial == "v")
    {
        return verticalGrav;
    }
    else
    {
        return 0.0f;
    }
}