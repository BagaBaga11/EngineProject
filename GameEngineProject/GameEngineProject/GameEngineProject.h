<<<<<<< Updated upstream
#pragma once
=======

#include "SDL.h"
>>>>>>> Stashed changes
class GameEngineProject
{
	public:
		void start(int sizeX, int sizeY);
};

class GameObject
{
public:

};

class Level
{
public:
<<<<<<< Updated upstream

=======
	void SetBackground(std::string image);	
	const std::string GetBackground() { return background; }
protected:
	std::string background;
>>>>>>> Stashed changes
};

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget);