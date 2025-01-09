#pragma once
#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <tuple>
#include <vector>
#include <Levels.h>
class XenonLevel : public Level
{
public:
    XenonLevel();
    ~XenonLevel();

    void Contact(GameObject* A, GameObject* B)override;
    std::vector<int> GetIndices(const std::string& input);
    void Display(const std::string& input, float x, float y, std::vector<Sprite*>* customLetters = nullptr);
    void UpdateScore(int scoreToAdd);
    void Update(float deltaTime) override;
private:
    char LetterMap[96] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
    };

    std::vector<Sprite*> letterforPoints;

    int points = 0;
};

