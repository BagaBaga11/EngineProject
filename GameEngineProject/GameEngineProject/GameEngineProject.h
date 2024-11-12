#pragma once
#include "SDL.h"
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
	void SetBackground(std::string image);	
	const std::string GetBackground() { return background; }
protected:
	std::string background;
};

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget);