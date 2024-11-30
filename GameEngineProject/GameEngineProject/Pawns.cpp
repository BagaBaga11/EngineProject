#include "Pawns.h"
#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Levels.h"
#include "GameObjects.h"
Pawn::Pawn(Level* mylevel) : GameObject(mylevel)
{
    keyState = SDL_GetKeyboardState(NULL);
}

Pawn::~Pawn()
{
}

void Pawn::CheckKeyboard()
{
    if ((keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) && (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]))
    {
        
    }   else if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D])
            Right();
        else if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A])
            Left();
    if ((keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) && (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]))
    {

    } else if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W])
        Up();
      else if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S])
        Down();
   
}

void Pawn::Right()
{
}

void Pawn::Left()
{
}

void Pawn::Up()
{
}

void Pawn::Down()
{
}

void Pawn::UpdateObject(float deltaTime)
{
    GameObject::UpdateObject(deltaTime);
    CheckKeyboard();
}