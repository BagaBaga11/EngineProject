#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "GameObjects.h"
#include "Pawns.h"
#include "SDL.h"

struct SDL_Texture;
struct SDL_Renderer;
class b2WorldId;
class GameObject;
class Sprite;
class b2ContactEvents;
class Pawn;

class Level
{
public:
	Level();
	~Level();
	void SetBackground(std::string image);
	const std::string GetBackground();

	virtual void Update(float deltaTime);

	std::vector<GameObject*> objectArray;
	std::vector<Sprite*> everyArray;
	//std::vector<GLuint*> bmpArray;

	SDL_Renderer* GiveRender();
	void SetRender(SDL_Renderer* rnd);
	void SetWorld(b2WorldId* world);
	b2WorldId* GetWorld() const;
	void SetGrav(float horizontal, float vertical);
	float GetGrav(const char* initial);

	void ProccesContact(b2ContactEvents sensorEvents);
	virtual void Contact(GameObject* A, GameObject* B);

	Pawn* GetPawn();
	void SetPawn(Pawn* pwn);

	virtual void UpdateUI();
protected:
	std::string background;
	SDL_Renderer* renderL = nullptr;
	b2WorldId* worldID = nullptr;
	float verticalGrav, horizontalGrav = 0;
	GameObject* ObjectA = nullptr;
	GameObject*	ObjectB = nullptr;
	Pawn* myPawn;
};

