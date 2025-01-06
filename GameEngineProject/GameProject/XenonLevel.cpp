#include "XenonLevel.h"
#include <iostream>
#include "Player.h"
#include "Rusher.h"
#include "Loner.h"
#include "Missile.h"


void XenonLevel::Contact(GameObject* A, GameObject* B)
{
    if (auto* player = dynamic_cast<Player*>(A))
    {
        if (auto* missile = dynamic_cast<Missile*>(B))
        {
            player->Hit();
            missile->Hit();
        }
        else if (auto* rusher = dynamic_cast<Rusher*>(B))
        {
            player->Hit();
            rusher->Hit();
        }
        else if (auto* loner = dynamic_cast<Loner*>(B))
        {
            player->Hit();
            loner->Hit();
        }
    }
    else if (auto* loner = dynamic_cast<Loner*>(A))
    {
        if (auto* missile = dynamic_cast<Missile*>(B))
        {

        }
        else if (auto* rusher = dynamic_cast<Rusher*>(B))
        {

        }
        else if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            loner->Hit();
        }
    }
    else if (auto* missile = dynamic_cast<Missile*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            missile->Hit();
        }
        else if (auto* rusher = dynamic_cast<Rusher*>(B))
        {

        }
        else if (auto* loner = dynamic_cast<Loner*>(B))
        {

        }
    }
    else if (auto* rusher = dynamic_cast<Rusher*>(A))
    {
        if (auto* player = dynamic_cast<Player*>(B))
        {
            player->Hit();
            rusher->Hit();
        }
        else if (auto* missile = dynamic_cast<Missile*>(B))
        {

        }
        else if (auto* loner = dynamic_cast<Loner*>(B))
        {

        }
    }
}
