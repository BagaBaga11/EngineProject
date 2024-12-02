
#include <iostream>
#include "Player.h"
#include "GameObjects.h"
#include <vector>
#include "GameEngineProject.h"
#include <random>
#include <string>


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
      /*  if (Enemies.size() <= 2)
        {
            std::random_device rd; 
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(0.0f, 500.0f);
            float random_float = dis(gen);
            GameObject* mon = new GameObject(mylevel);
            mon->SetBMP("graphics/LonerC.bmp", 4, 4, 32);
            mon->SetStartPos(random_float, -10.0f);
            mon->SetGravScale(30.0f);
            mon->SetSensor(false);
            mon->animationManager.AddAnimation("Loner", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
            mon->animationManager.SetCurrentAnimation("Loner");
            Enemies.push_back(mon);
        }*/
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


    Spaceship = new Player(mylevel);
    Spaceship->SetBMP("graphics/Ship2.bmp",7,3,64);
    Spaceship->SetStartPos(240.0f, 320.0f);
    Spaceship->SetGravScale(0.0f);
    Spaceship->SetSpeed(200.0f);
    Spaceship->SetSensor(true);
    //Spaceship->SetFilter(1);
    Spaceship->animationManager.AddAnimation("idle", { 3,17 }, 1.0f);
    Spaceship->animationManager.AddAnimation("tleft", { 2,1,0 }, 0.1f);
    Spaceship->animationManager.AddAnimation("tright", { 4,5,6 }, 0.1f);
    Spaceship->animationManager.SetCurrentAnimation("idle");

    GameObject* Loner = new GameObject(mylevel);
    Loner->SetBMP("graphics/LonerC.bmp", 4,4 ,32);
    Loner->SetStartPos(400.0f, 0.0f);
    Loner->SetGravScale(30.0f);
    Loner->SetSensor(false);
    Loner->animationManager.AddAnimation("Loner", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
    Loner->animationManager.SetCurrentAnimation("Loner");
    //Loner->SetFilter(3);
    Enemies.push_back(Loner);

    GameObject* Loner2 = new GameObject(mylevel);
    Loner2->SetBMP("graphics/LonerC.bmp", 4, 4, 32);
    Loner2->SetStartPos(200.0f, 0.0f);
    Loner2->SetGravScale(10.0f);
    Loner2->SetSensor(false);
    Loner2->animationManager.AddAnimation("Loner", {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }, 0.1f);
    Loner2->animationManager.SetCurrentAnimation("Loner");
    Enemies.push_back(Loner2);
    

    engine.Start(640,480);
    Update();
    engine.End();

    for (size_t i = 0; i < mylevel->objectArray.size(); i++)
    {
        delete(mylevel->objectArray[i]);
    }
    delete(mylevel);
    
    return 0;
}


