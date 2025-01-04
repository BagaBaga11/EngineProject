

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Levels.h"
#include "Pawns.h"
#include <random>
#include "glad/glad.h"
#include "stb_image.h"

void GameEngine::Start(int sizeX, int sizeY)
{
    SDL_Init(SDL_INIT_VIDEO);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    ev = new SDL_Event;
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ myLevel->GetGrav("h"), myLevel->GetGrav("v")};
    b2WorldId* worl = new b2WorldId(b2CreateWorld(&worldDef));
    myLevel->SetWorld(worl);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{ 240.0f, 680.0f };
    b2BodyId groundId = b2CreateBody(*worl, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(1500.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        SDL_Quit();
    }
}
bool GameEngine::Update(float deltaTime)
{          

        while (SDL_PollEvent(ev))
        {
            if (ev->type == SDL_QUIT)
            return false;
        }
        myLevel->Update(deltaTime);
     /*   for (size_t i = 0; i < myLevel->bmpArray.size(); ++i)
        { 
            myLevel->everyArray.Draw();
        }*/
        SDL_GL_SwapWindow(window);

        return true;
}

void GameEngine::End()
{
    delete ev;
    glBindVertexArray(0);
    b2DestroyWorld(*myLevel->GetWorld());
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

float GameEngine::getRandomFloat(float min, float max) 
{
    static std::random_device rd;          
    static std::mt19937 gen(rd());           
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);                    
}

bool GameEngine::RandomBool()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::bernoulli_distribution dist(0.5);

    return dist(gen);
}

