#include "XenonLevel.h"
#include <iostream>
#include "Player.h"
#include "FriendlyMissile.h"
#include "Enemy.h"
#include "EnemyMissile.h"


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
    }
    else if (auto* friendlyMissile = dynamic_cast<FriendlyMissile*>(A))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(B))
        {
            friendlyMissile->Hit();
            enemy->Hit();
        }
        else if (auto* enemyMissile = dynamic_cast<EnemyMissile*>(B))
        {
            friendlyMissile->Hit();
            enemyMissile->Hit();
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
        }
    }
}
