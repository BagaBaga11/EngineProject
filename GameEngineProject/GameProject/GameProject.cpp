
#include <iostream>
#include "Player.h"
#include "GameObjects.h"
#include "Sprite.h"
#include <vector>
#include "GameEngineProject.h"
#include <random>
#include <string>
#include "Loner.h"
#include "Rusher.h"


GameEngine engine;
Player* Spaceship;   
Level* mylevel;

std::vector<GameObject*> Enemies;

void Update()
{
    bool isRunning = true;
    int last = 0;
    float deltaTime;
    int now = 0;
    while (isRunning)
    {
        last = now;
        now = engine.Tick();
        deltaTime = (now - last) / 1000.0f;
        isRunning = engine.Update(deltaTime) && Spaceship->GetAlive();
    }
}

int main(int argc, char* argv[])
{
    Level* mylevel = new Level;
    mylevel->SetBackground("graphics/galaxy2.bmp");
    mylevel->SetGrav(0.0f, 1.0f);
    engine.SetLevel(mylevel);
    engine.Start(640,480);

    Spaceship = new Player(mylevel);

    Loner* lone = new Loner(mylevel,engine);
    Enemies.push_back(lone);

    Rusher* lone2 = new Rusher(mylevel, engine);
    Enemies.push_back(lone2);

    Sprite* Wall = new Sprite(mylevel);
    Wall->SetBMP("graphics/SAster96.bmp", 5, 5, 64);
    Wall->SetStartPos(200.0f, 0.0f);
    Wall->animationManager.AddAnimation("Wall", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24, }, 0.1f);
    Wall->animationManager.SetCurrentAnimation("Wall");
    Wall->StartObject();


    Update();
    engine.End();

    for (size_t i = 0; i < mylevel->everyArray.size(); i++)
    {
        delete(mylevel->everyArray[i]);
    }
    delete(mylevel);
    
    return 0;
}


