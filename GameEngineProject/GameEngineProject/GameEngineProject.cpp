

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Levels.h"
#include "Pawns.h"


void GameEngine::Start(int sizeX, int sizeY)
{
    ev = new SDL_Event;
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ myLevel->GetGrav("h"), myLevel->GetGrav("v")};
    b2WorldId* worl = new b2WorldId(b2CreateWorld(&worldDef));
    myLevel->SetWorld(worl);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{ 240.0f, 680.0f };
    b2BodyId groundId = b2CreateBody(*myLevel->GetWorld(), &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(1500.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
   // groundShapeDef.filter.categoryBits = Cat::Walls;
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
bool GameEngine::Update(float deltaTime)
{          

        while (SDL_PollEvent(ev))
        {
            if (ev->type == SDL_QUIT)
            return false;
        }
        SDL_RenderClear(render);
        SDL_RenderCopy(render, backgroundTexture, NULL, NULL);
        for (size_t i = 0; i < myLevel->bmpArray.size(); ++i)
        { 
            SDL_RenderCopy(render, myLevel->bmpArray[i], myLevel->objectArray[i]->objRect , myLevel->objectArray[i]->objPosition);
        }
        SDL_RenderPresent(render);
        myLevel->Update(deltaTime);
        return true;
}

void GameEngine::End()
{
    delete ev;
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


