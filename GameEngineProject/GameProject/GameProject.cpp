
#include <iostream>
#include "GameEngineProject.h"

int main(int argc, char* argv[])
{
    GameEngineProject engine;
    Level mylevel;
    mylevel.SetBackground("galaxy2.bmp");
    engine.start(650,480);
    return 0;
}

