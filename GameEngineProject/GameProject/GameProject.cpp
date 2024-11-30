
#include <iostream>
#include "GameEngineProject.h"
#include "Player.h"

GameEngine engine;

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
        isRunning = engine.Update(deltaTime);
    }
}

int main(int argc, char* argv[])
{
    Level* mylevel = new Level;
    mylevel->SetBackground("graphics/galaxy2.bmp");
    mylevel->SetGrav(0.0f, 1.0f);
    engine.SetLevel(mylevel);


    Player* Spaceship = new Player(mylevel);
    Spaceship->SetBMP("graphics/Ship2.bmp",7,3,64);
    Spaceship->SetStartPos(0.0f, 0.0f);
    Spaceship->SetGravScale(0.0f);
    Spaceship->SetSpeed(200.0f);
    Spaceship->animationManager.AddAnimation("idle", { 3,17 }, 5.0f);
    Spaceship->animationManager.AddAnimation("tleft", { 2,1,0 }, 0.2f);
    Spaceship->animationManager.AddAnimation("tright", { 4,5,6 }, 0.2f);
    Spaceship->animationManager.SetCurrentAnimation("idle");

    GameObject* Loner = new GameObject(mylevel);
    Loner->SetBMP("graphics/LonerC.bmp", 4,4 ,32);
    Loner->SetStartPos(400.0f, 0.0f);
    Loner->SetGravScale(0.15f);

    engine.Start(640,480);
    Update();
    engine.End();
    delete(mylevel);
    delete(Spaceship);
    delete(Loner);
    
    return 0;
}


