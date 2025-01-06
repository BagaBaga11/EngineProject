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
    for (size_t i = 0; i < everyArray.size(); ++i)
    {
        everyArray[i]->Update(deltaTime);
    }
    b2ContactEvents sensorEvents = b2World_GetContactEvents(*GetWorld());
    ProccesContact(sensorEvents);

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

void Level::ProccesContact(b2ContactEvents sensorEvents)
{
    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {

        b2ContactBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
        for (size_t t = 0; t < objectArray.size(); t++)
        {
            GameObject* object = objectArray[t];
            if (object)
            {
                if ((object->GetShape()->index1 == beginTouch->shapeIdA.index1) && (object->GetShape()->world0 == beginTouch->shapeIdA.world0) && (object->GetShape()->revision == beginTouch->shapeIdA.revision))
                {
                    ObjectA = object;
                }
                if ((object->GetShape()->index1 == beginTouch->shapeIdB.index1) && (object->GetShape()->world0 == beginTouch->shapeIdB.world0) && (object->GetShape()->revision == beginTouch->shapeIdB.revision))
                {
                    ObjectB = object;
                }
            }
        }
        if (ObjectA && ObjectB)
        {
            Contact(ObjectA, ObjectB);
        }
    }
}

void Level::Contact(GameObject* A, GameObject* B)
{
}
