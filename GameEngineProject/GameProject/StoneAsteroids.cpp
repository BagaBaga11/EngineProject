#include "StoneAsteroids.h"
#include "GameEngineProject.h"

StoneAsteroids::StoneAsteroids(Level* mylevel, GameEngine engine) : Asteroids(mylevel), asteroidType(MainAsteroid)
{
	Engine = engine;
	SetGravScale(1.0f);
	SetSensor(false);
    SetDestruction(true);
	animationManager.AddAnimation("Asteroid", { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 }, 0.1f);
	animationManager.SetCurrentAnimation("Asteroid");
}

StoneAsteroids::~StoneAsteroids()
{
}

void StoneAsteroids::Update(float deltaTime)
{
    GetPosition();
    switch (asteroidType)
    {
    case MainAsteroid:
        SetPos(Firstpos, Secondpos, 0);
        break;

    case RightAsteroid:
        SetPos(Secondpos, Secondpos, 0);
        break;

    case LeftAsteroid:
        SetPos(Secondpos* -1, Secondpos, 0);
        break;

    default:
        break;
    }
    
    GameObject::Update(deltaTime);

}

void StoneAsteroids::Hit()
{
    if(Spawnasteroids == true)
    {
        StoneAsteroids* StoneAsteroid1 = new StoneAsteroids(mylevel, Engine);
        StoneAsteroid1->SetBMP("graphics/SAster32.bmp", 8, 2, 1);
        StoneAsteroid1->Setoffset(0.0f);
        StoneAsteroid1->SetStartPos(Firstpos, Secondpos);
        StoneAsteroid1->SetDestruction(false);
        StoneAsteroid1->asteroidType = MainAsteroid;
        StoneAsteroid1->StartObject();

        StoneAsteroids* StoneAsteroid2 = new StoneAsteroids(mylevel, Engine);
        StoneAsteroid2->SetBMP("graphics/SAster32.bmp", 8, 2, 1);
        StoneAsteroid2->Setoffset(100.0f);
        StoneAsteroid2->SetStartPos(Firstpos + 10.0f, Secondpos + 5.0f);
        StoneAsteroid2->SetDestruction(false);
        StoneAsteroid2->asteroidType = RightAsteroid;
        StoneAsteroid2->StartObject();

        StoneAsteroids* StoneAsteroid3 = new StoneAsteroids(mylevel, Engine);
        StoneAsteroid3->SetBMP("graphics/SAster32.bmp", 8, 2, 1);
        StoneAsteroid3->Setoffset(-100.0f);
        StoneAsteroid3->SetStartPos(Firstpos - 10.0f, Secondpos + 5.0f);
        StoneAsteroid3->SetDestruction(false);
        StoneAsteroid3->asteroidType = LeftAsteroid;
        StoneAsteroid3->StartObject();

        delete this;
    }
    else
    {
        delete this;
    }
    
}

void StoneAsteroids::Setoffset(float off)
{
	Offset = off;
}

void StoneAsteroids::SetDestruction(bool spawnasteroids)
{
    Spawnasteroids = spawnasteroids;
}
