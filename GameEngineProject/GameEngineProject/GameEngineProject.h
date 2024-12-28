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
typedef unsigned int GLuint;

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
		GLuint* ebo;
		GLuint* vbo;
		GLuint* vao;
protected:
		Level* myLevel = nullptr;
		SDL_Renderer* render = nullptr;
		GLuint* backgroundTexture = nullptr;
		SDL_Window* window = nullptr;
		SDL_Event* ev = nullptr;
		GLuint* vertexShader;
		GLuint* fragmentShader;
		GLuint* shaderProgram;
};
