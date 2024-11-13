

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"

void GameEngineProject::start(int sizeX, int sizeY)
{
    bool isRunning = true;
    b2WorldDef worldDef = b2DefaultWorldDef();

    b2Vec2 gravity = { 0.0f, -10.0f };
    worldDef.gravity = gravity;

    b2WorldId worldId = b2CreateWorld(&worldDef);

    SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    SDL_Texture* backgroundTexture = LoadTexture(myLevel.GetBackground(), render);

    while (isRunning)
    {
        SDL_RenderClear(render);
        SDL_RenderCopy(render, backgroundTexture, NULL, NULL);
        SDL_RenderPresent(render);
    }

    SDL_DestroyWindow(window);
}

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == NULL)
    {
        std::cout << "Error" << std::endl;
    }
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
