
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
#include "XenonLevel.h"
#include "PowerHealth.h"
#include "StoneAsteroids.h"
#include "MetalAsteroids.h"
#include "Drone.h"
#include "PowerBullet.h"
#include "Companion.h"


GameEngine engine;
Player* Spaceship;   
XenonLevel* mylevel;

std::vector<GameObject*> Enemies;
float timeEnem;
float timeStone;
float timeUpgr;
int drone = 0;
float timeDrone;

void Spawn(float deltaTime)
{
    timeEnem += deltaTime;
    timeDrone += deltaTime;
    if (timeEnem > 15)
    {
        drone += 1;
        bool Enemspawn = engine.RandomBool();
        if (Enemspawn)
        {
            Loner* lone = new Loner(mylevel, engine);
            Enemies.push_back(lone);
            lone->StartObject();
        }
        else
        {
            Rusher* rusher = new Rusher(mylevel, engine);
            Enemies.push_back(rusher);
            rusher->StartObject();
        }
        if (drone > 3)
        {
            int distancedrone = 0;
            float value = engine.getRandomFloat(100, 400);
            for (size_t i = 0; i < 5; i++)
            {
                Drone* drone = new Drone(mylevel, engine);
                drone->SetStartPos(value, -30.0f + distancedrone);
                drone->StartObject();
                distancedrone -= 50;
            }
            drone = 0;
        }
        timeEnem = 0;
    }   
}
void SpawnUpgr(float deltaTime)
{ 
    timeUpgr += deltaTime;
        if (timeUpgr > 20)
        {
            bool Powerspawn = engine.RandomBool(); 
            if (Powerspawn)
            {
                PowerHealth* powerhealth = new PowerHealth(mylevel, engine);
                powerhealth->StartObject();
            }
            else
            {
                PowerBullet* powerbullet = new PowerBullet(mylevel, engine);
                powerbullet->StartObject();
                if (Spaceship->GetComp() == nullptr)
                {
                    Companion* s = new Companion(mylevel, engine);
                    s->StartObject();
                }
            }
            timeUpgr = 0;
        }
}
void SpawnStones(float deltaTime)
{
    timeStone += deltaTime;
    if (timeStone > 5)
    {
        bool Asteroids = engine.RandomBool();
        if (Asteroids)
        {
            bool Stonesize = engine.RandomBool();
            StoneAsteroids* StoneAsteroid = new StoneAsteroids(mylevel, engine);
            if (Stonesize)
            {
                StoneAsteroid->SetBMP("graphics/SAster96.bmp", 5, 5, 4);
            }
            else
            {
                StoneAsteroid->SetBMP("graphics/SAster64.bmp", 8, 3, 2);
            }
            float value = engine.getRandomFloat(0, 460);
            StoneAsteroid->SetStartPos(value, -100.0f);
            StoneAsteroid->StartObject();

        }
        else
        {
            MetalAsteroids* MetalAsteroid = new MetalAsteroids(mylevel, engine);
            MetalAsteroid->SetBMP("graphics/MAster96.bmp", 5, 5, 4);
            float value1 = engine.getRandomFloat(0, 460);
            MetalAsteroid->SetStartPos(value1, -100.0f);
            MetalAsteroid->StartObject();
        }
        timeStone = 0;
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
        SpawnStones(deltaTime);
        SpawnUpgr(deltaTime);
        isRunning = engine.Update(deltaTime) && Spaceship->GetAlive();
    } 
}

int main(int argc, char* argv[])
{
    mylevel = new XenonLevel;
    mylevel->SetGrav(0.0f, 1.0f);
    engine.SetLevel(mylevel);
    engine.Start(640,480);

    Sprite* BackGround = new Sprite(mylevel);
    BackGround->SetBMP("graphics/galaxy2.bmp", 1, 1, 40);
    BackGround->animationManager.AddAnimation("Idle", { 1 }, 999999999);
    BackGround->animationManager.SetCurrentAnimation("Idle");
    BackGround->StartObject();

    Spaceship = new Player(mylevel);
    Spaceship->StartObject();

    mylevel->Display("Score", 15, 15);
    mylevel->UpdateScore(0);
    mylevel->StartUI();

    Update();
    engine.End();

    for (size_t i = 0; i < mylevel->everyArray.size(); i++)
    {
        delete(mylevel->everyArray[i]);
    }
    delete(mylevel);
    
    return 0;
}


