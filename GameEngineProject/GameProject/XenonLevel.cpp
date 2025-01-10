#include "XenonLevel.h"
#include <iostream>
#include "Player.h"
#include "FriendlyMissile.h"
#include "Enemy.h"
#include "EnemyMissile.h"
#include <iomanip>
#include <sstream>
#include "Collectibles.h"
#include "StoneAsteroids.h"
#include "MetalAsteroids.h"

XenonLevel::XenonLevel()
{
}

XenonLevel::~XenonLevel()
{
}
void XenonLevel::Contact(GameObject* A, GameObject* B)
{
    if (!A || !B)
    {
        return;
    }

    if (auto* player = dynamic_cast<Player*>(A))
    {
        if (auto* enemyMissile = dynamic_cast<EnemyMissile*>(B))
        {
            player->Hit();
            enemyMissile->Hit();
        }
        else if (auto* enemy = dynamic_cast<Enemy*>(B))
        {
            player->Hit();
            enemy->Hit();
        }
        else if (auto* collectible = dynamic_cast<Collectibles*>(B))
        {
            collectible->Upgrade(A);
        }
        else if (auto* stone = dynamic_cast<StoneAsteroids*>(B))
        {
            player->Hit();
            stone->Hit();
        }
        else if (auto* metal = dynamic_cast<MetalAsteroids*>(B))
        {
            player->Hit();
            metal->Hit();
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            if (player->GetComp() == nullptr)
            {
                companion->Attach();
                player->SetComp(companion);
            }
        }
    }
    else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(A))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(B))
        {
            friendlyMissile->Hit();
            enemy->Hit();
            UpdateScore(100);
        }
        else if (auto* enemyMissile = dynamic_cast<EnemyMissile*>(B))
        {
            friendlyMissile->Hit();
            enemyMissile->Hit();
        }
        else if (auto* stone = dynamic_cast<StoneAsteroids*>(B))
        {
            friendlyMissile->Hit();
            stone->Hit();
        }
        else if (auto* metal = dynamic_cast<MetalAsteroids*>(B))
        {
            friendlyMissile->Hit();
        }
    }
    else if (auto* enemyMissile = dynamic_cast<EnemyMissile*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            enemyMissile->Hit();
        }
        else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(B))
        {
            friendlyMissile->Hit();
            enemyMissile->Hit();
        }
        else if (auto* metal = dynamic_cast<MetalAsteroids*>(B))
        {
            enemyMissile->Hit();
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                enemyMissile->Hit();
            }
        }
    }
    else if (auto* enemy = dynamic_cast<Enemy*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            enemy->Hit();
        }
        else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(B))
        {
            friendlyMissile->Hit();
            enemy->Hit();
            UpdateScore(100);
        }
        else if (auto* metal = dynamic_cast<MetalAsteroids*>(B))
        {
            enemy->Hit();
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                enemy->Hit();
            }
        }
    }
    else if (auto* collectible = dynamic_cast<Collectibles*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            collectible->Upgrade(B);
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            collectible->Upgrade(B);
        }
    }
    else if (auto* stone = dynamic_cast<StoneAsteroids*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            stone->Hit();
        }
        else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(B))
        {
            friendlyMissile->Hit();
            stone->Hit();
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                stone->Hit();
            }
        }
    }
    else if (auto* metal = dynamic_cast<MetalAsteroids*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            metal->Hit();
        }
        else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(B))
        {
            friendlyMissile->Hit();
        }
        else if (auto* companion = dynamic_cast<Companion*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                metal->Hit();
            }
        }
    }
    else if (auto* companion = dynamic_cast<Companion*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            if (player->GetComp() == nullptr)
            {
                companion->Attach();
                player->SetComp(companion);
            }
        }
        else if (auto* enemyMissile = dynamic_cast<EnemyMissile*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                enemyMissile->Hit();
            }
        }
        else if (auto* enemy = dynamic_cast<Enemy*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                enemy->Hit();
            }
        }
        else if (auto* collectible = dynamic_cast<Collectibles*>(B))
        {
            collectible->Upgrade(A);
        }
        else if (auto* stone = dynamic_cast<StoneAsteroids*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                stone->Hit();
            }
        }
        else if (auto* metal = dynamic_cast<MetalAsteroids*>(B))
        {
            if (companion->Getbool())
            {
                companion->Hit();
                metal->Hit();
            }
        }
    }
}
std::vector<int> XenonLevel::GetIndices(const std::string& input)
{
    std::vector<int> indices;

    for (char c : input) {
        bool found = false;

        for (int i = 0; i < 96; ++i) {
            if (LetterMap[i] == c) {
                indices.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) {
            indices.push_back(-1);
        }
    }
    return indices;
}

void XenonLevel::Display(const std::string& input, float x, float y, std::vector<Sprite*>* customLetters)
{
    float distance = 0;
    std::vector<int> indices = GetIndices(input);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        Sprite* letter = new Sprite(this);
        letter->SetBMP("graphics/font16x16.bmp", 8, 12, 1);
        letter->animationManager.AddAnimation("Default", { indices[i] + 1 }, 20);
        letter->animationManager.SetCurrentAnimation("Default");
        letter->SetPos(x + distance, y, 0);
        letter->StartObject();
        distance += 12.0f;
        if (customLetters != nullptr)
        {
            customLetters->push_back(letter);
        }
    }
}

void XenonLevel::UpdateScore(int scoreToAdd)
{
    std::ostringstream oss;

    points += scoreToAdd;
    oss << std::setw(6) << std::setfill('0') << points;

    for (Sprite* sprite : letterforPoints)
    {
        delete sprite;
    }
    letterforPoints.clear();

    Display(oss.str(), 80, 15, &letterforPoints);
}

void XenonLevel::Update(float deltaTime)
{
    for (size_t i = 0; i < everyArray.size(); ++i)
    {
        if (everyArray[i]->GetXPos() > 500 || everyArray[i]->GetXPos() < -100 )
        {
            delete everyArray[i];
        }
        else if (everyArray[i]->GetYPos() > 700 || everyArray[i]->GetYPos() < -300)
        {
            delete everyArray[i];
        }
    }
    Level::Update(deltaTime);
}

void XenonLevel::UpdateUI()
{
    if (auto* player = dynamic_cast<Player*>(myPawn))
    {
        int health = player->GetHealth();
        if (health >= 0 && health <= 2)
        {
            Lives[health]->animationManager.SetCurrentAnimation("Dead");
        }
    }
}

void XenonLevel::StartUI()
{
    float distance = 0.0f;
    auto* player = dynamic_cast<Player*>(myPawn);
    for (size_t i = 0; i < 3; i++)
    {
        Sprite* spr = new Sprite(this);
        spr->SetBMP("graphics/Ship2.bmp", 7, 3, 2);
        spr->animationManager.AddAnimation("Default", { 4 }, 20);
        spr->animationManager.AddAnimation("Dead", { 11 }, 20);
        spr->animationManager.SetCurrentAnimation("Default");
        spr->SetPos(20 + distance, 600, 0);
        spr->StartObject();
        Lives.push_back(spr);
        distance += 20;
    }
}
