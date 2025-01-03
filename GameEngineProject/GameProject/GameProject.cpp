
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
float times;

void Spawn(float deltaTime)
{
    times += deltaTime;
    if (times > 5)
    {
        bool spawn = engine.RandomBool();
        if (spawn)
        {
            Loner* lone = new Loner(mylevel, engine);
            Enemies.push_back(lone);
        }else
        {
            Rusher* rusher = new Rusher(mylevel, engine);
            Enemies.push_back(rusher);
        }
        times = 0;
    }
}
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
        
        Spawn(deltaTime);
        isRunning = engine.Update(deltaTime) && Spaceship->GetAlive();
    } 
}

int main(int argc, char* argv[])
{
    mylevel = new Level;
    mylevel->SetBackground("graphics/galaxy2.bmp");
    mylevel->SetGrav(0.0f, 1.0f);
    engine.SetLevel(mylevel);
    engine.Start(640,480);

    Spaceship = new Player(mylevel);

    //Loner* lone = new Loner(mylevel,engine);
    //Enemies.push_back(lone);

    //Rusher* rusher = new Rusher(mylevel, engine);
    //Enemies.push_back(rusher);

    Update();
    engine.End();

    for (size_t i = 0; i < mylevel->everyArray.size(); i++)
    {
        delete(mylevel->everyArray[i]);
    }
    delete(mylevel);
    
    return 0;
}


