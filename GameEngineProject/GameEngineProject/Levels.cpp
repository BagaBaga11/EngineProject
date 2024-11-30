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
    for (size_t i = 0; i < objectArray.size(); ++i)
    {
        if (objectArray[i]->GetGravScale() != 0.0f)
        {
            float timeStep = 1.0f / 60.0f;
            int subStepCount = 4;
            for (int t = 0; t < 10; ++t)
            {

                b2World_Step(*GetWorld(), timeStep, subStepCount);
                b2BodyId bod = *objectArray[i]->Getbody();
                b2Vec2 position = b2Body_GetPosition(bod);
                objectArray[i]->newposX = position.x;
                objectArray[i]->newposY = position.y;
            }
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