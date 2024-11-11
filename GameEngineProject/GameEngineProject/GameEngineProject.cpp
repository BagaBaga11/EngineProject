

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"

void GameEngineProject::start(int sizeX, int sizeY)
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    b2Vec2 gravity = { 0.0f, -10.0f };
    worldDef.gravity = gravity;
    b2WorldId worldId = b2CreateWorld(&worldDef);

    SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, 0);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
}
