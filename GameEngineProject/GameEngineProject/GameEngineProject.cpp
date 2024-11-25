

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>

b2WorldId worl;

void GameEngine::Start(int sizeX, int sizeY)
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    worl = b2CreateWorld(&worldDef);
    myLevel->SetWorld(&worl);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{ 0.0f, -10.0f };
    b2BodyId groundId = b2CreateBody(*myLevel->GetWorld(), &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    myLevel->SetRender(render);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    backgroundTexture = LoadTexture(myLevel->GetBackground(), render);
    for (size_t i = 0; i < myLevel->objectArray.size(); i++)
    {
        myLevel->objectArray[i]->StartObject();
    }
}
void GameEngine::Update(float deltaTime)
{  
        myLevel->Update(deltaTime);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, backgroundTexture, NULL, NULL);
        for (size_t i = 0; i < myLevel->bmpArray.size(); ++i)
        { 
            SDL_RenderCopy(render, myLevel->bmpArray[i], myLevel->objectArray[i]->objRect , myLevel->objectArray[i]->objPosition);
        }
        SDL_RenderPresent(render);
}

void GameEngine::End()
{
    b2DestroyWorld(*myLevel->GetWorld());
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}

void GameEngine::SetLevel(Level* level)
{
    myLevel = level;
}

int GameEngine::Tick()
{
    return SDL_GetTicks();
}

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == NULL)
    {
        std::cout << "bruh" << std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            std::cout << "Errodr" << std::endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

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
        float timeStep = 1.0f / 60.0f;
        int subStepCount = 4;
        for (int i = 0; i < 60; ++i)
        {
            b2World_Step(*GetWorld(), timeStep, subStepCount);
            for (size_t i = 0; i < objectArray.size(); i++)
            {
                 b2Vec2 position = b2Body_GetPosition(objectArray[i]->Getbody());
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

GameObject::GameObject(Level* mylevel) : mylevel(mylevel)
{
    if (mylevel != nullptr)
    {
        mylevel->objectArray.push_back(this);
    }

}

GameObject::~GameObject()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    delete objRect;
    delete objPosition;
   if (mylevel != nullptr)
    {
        auto it = std::find(mylevel->objectArray.begin(), mylevel->objectArray.end(), this);
        if (it != mylevel->objectArray.end())
        {
            mylevel->objectArray.erase(it);
        }
    }
}

void GameObject::UpdateObject(float deltaTime)
{
    static bool Active = true;
    if (myBMP != "0" && mylevel->GiveRender() != nullptr && Active)
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
        objPosition = SetRect(newposX, newposY, bmpSectionSize, bmpSectionSize);

        Active = false;
    } 
    frameTime += deltaTime;
    if (frameTime >= 0.05f)
    {
        frameTime = 0;
        objRect->x += frameWidth;
        if (objRect->x >= textureWidth) {
            objRect->x = 0;
            objRect->y += frameHeight;
            if (objRect->y >= textureHeight) {
                objRect->y = 0;
            }
        }
    }
}

void GameObject::SetBMP(std::string image, int wSec, int hSec, int secSize)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    myBMP = image;
    widthSection = wSec;
    heightSection = hSec;
    bmpSectionSize = secSize;
}
void GameObject::StartObject()
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 0.0f, 4.0f };
    b2BodyId bodyId = b2CreateBody(*mylevel->GetWorld(), &bodyDef);
    SetBody(bodyId);
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

b2BodyId GameObject::Getbody()
{
    return bodyID;
}

void GameObject::SetBody(b2BodyId body)
{
    bodyID = body;
}
