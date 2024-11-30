#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "GameEngineProject.h"
#include "GameObjects.h"


struct SDL_Renderer;
struct b2WorldId;
class GameObject;

class Level
{
public:
	Level();
	~Level();
	void SetBackground(std::string image);
	const std::string GetBackground();

	void Update(float deltaTime);

	std::vector<GameObject*> objectArray;
	std::vector<SDL_Texture*> bmpArray;

	SDL_Renderer* GiveRender();
	void SetRender(SDL_Renderer* rnd);
	void SetWorld(b2WorldId* world);
	b2WorldId* GetWorld() const;
	void SetGrav(float horizontal, float vertical);
	float GetGrav(const char* initial);
protected:
	std::string background;
	SDL_Renderer* renderL = nullptr;
	b2WorldId* worldID;
	float verticalGrav, horizontalGrav = 0;
};

