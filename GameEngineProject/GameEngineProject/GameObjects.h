#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "Levels.h"
#include "GameEngineProject.h"
#include "Animation.h"


struct SDL_Texture;
struct SDL_Rect;
typedef struct b2BodyId;
class Level;


class GameObject
{
public:
	explicit GameObject(Level* mylevel);
	~GameObject();
	void StartObject();
	virtual void UpdateObject(float deltaTime);
	void SetBMP(std::string image, int wSec, int hSec, int objsize);
	std::string GetBMP();

	SDL_Rect* SetRect(int x, int y, int w, int h);
	SDL_Texture* GetTexture();


	SDL_Rect* objRect;
	SDL_Rect* objPosition;

	b2BodyId* Getbody();
	void SetStartPos(float x, float y);
	float newposX;
	float newposY;

	void SetGravScale(float scale);
	float GetGravScale();

	Animation animationManager;
protected:
	b2BodyId* bodyID;
	SDL_Texture* texture = nullptr;
	std::string myBMP = "0";
	Level* mylevel;
	float starposX;
	float starposY;
	float scaleGrav = 1.0f;

	int textureWidth, textureHeight = 0;
	int frameWidth, frameHeight = 0;
	int widthSection, heightSection = 0;
	float frameTime = 0;
	int objSize = 0;
};

