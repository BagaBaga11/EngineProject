#pragma once
#include "Animation.h"

class SDL_Texture;
class Sprite
{
public:
	Animation animationMan;

	Sprite();
	~Sprite();

	void SetBMP(std::string image, int wSec, int hSec, int objsize);
	void Update(float deltaTime);
protected:
	SDL_Texture* texture = nullptr;

	int textureWidth, textureHeight = 0;
	int frameWidth, frameHeight = 0;
	int widthSection, heightSection = 0;
	float frameTime = 0;
	int objSize = 0;
	std::string myBMP = "0";
	SDL_Rect* objRect;
	SDL_Rect* objPosition;
};

