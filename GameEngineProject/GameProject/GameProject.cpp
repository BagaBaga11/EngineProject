
#include <iostream>
#include "GameEngineProject.h"

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
        engine.Update(deltaTime);
    }
}

int main(int argc, char* argv[])
{
    Level* mylevel = new Level;
    mylevel->SetBackground("graphics/galaxy2.bmp");
    engine.SetLevel(mylevel);

    GameObject* drone = new GameObject(mylevel);
    drone->SetBMP("graphics/drone.bmp",8,2,32);

    engine.Start(640,480);
    Update();
    engine.End();
    delete(mylevel);
    delete(drone);
    
    return 0;
}


