

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"

void GameEngineProject::start()
{

    SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Delay(5000);
}
