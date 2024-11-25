#pragma once
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Window;
struct b2WorldId;
struct b2BodyId;
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
protected:
	std::string background;
	SDL_Renderer* renderL = nullptr;
	b2WorldId* worldID;
};

class GameObject
{
public:
	GameObject(Level* mylevel);
	~GameObject();
	void StartObject();
	void UpdateObject(float deltaTime);
	void SetBMP(std::string image, int wSec, int hSec, int secSize);
	std::string GetBMP();

	SDL_Rect* SetRect(int x, int y, int w, int h);
	SDL_Texture* GetTexture();

	int textureWidth, textureHeight = 0;
	int frameWidth, frameHeight = 0;
	int widthSection, heightSection = 0;
	int bmpSectionSize = 0;
	float frameTime = 0;

	SDL_Rect* objRect;
	SDL_Rect* objPosition;

	b2BodyId Getbody();
	void SetBody(b2BodyId body);
	float newposX = 0;
	float newposY = 0;
protected:
	b2BodyId bodyID;
	SDL_Texture* texture = nullptr;
	std::string myBMP = "0";
	Level* mylevel;

};


class GameEngine
{
	public:
		void Start(int sizeX, int sizeY);
		void Update(float deltaTime);
		void End();

		void SetLevel(Level* level);
		int Tick();
protected:
		Level* myLevel = nullptr;
		SDL_Renderer* render = nullptr;
		SDL_Texture* backgroundTexture = nullptr;
		SDL_Window* window = nullptr;
};

struct SDL_Texture* LoadTexture(std::string filePath, struct SDL_Renderer* renderTarget);
