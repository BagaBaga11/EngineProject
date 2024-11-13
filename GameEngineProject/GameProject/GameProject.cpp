
#include <iostream>
#include "GameEngineProject.h"

int main(int argc, char* argv[])
{
    GameEngineProject engine;
    Level mylevel;
    mylevel.SetBackground("graphics/galaxy2.bmp");
    engine.SetLevel(mylevel);
    engine.start(640,480);
    return 0;
}

