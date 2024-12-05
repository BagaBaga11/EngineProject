#pragma once
#include <iostream>
#include <vector>
#include "Levels.h"
#include "Pawns.h"


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Window;
union SDL_Event;
class Level;
class GameObject;
class Pawn;

class GameEngine
{
	public:
		void Start(int sizeX, int sizeY);
		bool Update(float deltaTime);
		void End();

		void SetLevel(Level* level);
		int Tick();
		float getRandomFloat(float min, float max);
		bool RandomBool();
protected:
		Level* myLevel = nullptr;
		SDL_Renderer* render = nullptr;
		SDL_Texture* backgroundTexture = nullptr;
		SDL_Window* window = nullptr;
		SDL_Event* ev = nullptr;
};


struct SDL_Texture* LoadTexture(std::string filePath, struct SDL_Renderer* renderTarget);
