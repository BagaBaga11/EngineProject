#pragma once
#include "SDL.h"


class GameObject
{
public:

};

static class Level
{
public:
	void SetBackground(std::string image) { background = image; }
	const std::string GetBackground() { return background; }
protected:
	std::string background;
};

class GameEngineProject
{
	public:
		void start(int sizeX, int sizeY);
		void SetLevel(Level level) {myLevel = level;};
protected:
		Level myLevel;
};
SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget);