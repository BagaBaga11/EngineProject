

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"

void GameEngineProject::start(int sizeX, int sizeY)
{
    bool isRunning = true;
    Level mylevel;

    b2WorldDef worldDef = b2DefaultWorldDef();

    b2Vec2 gravity = { 0.0f, -10.0f };
    worldDef.gravity = gravity;

    b2WorldId worldId = b2CreateWorld(&worldDef);

    SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, 0);
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* backgroundTexture = LoadTexture(mylevel.GetBackground(), render);

    while (isRunning)
    {
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
}

void Level::SetBackground(std::string imageName)
{
    background = imageName;
}

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == NULL)
        std::cout << "MegaError" << std::endl;
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            std::cout << "Error" << std::endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}
