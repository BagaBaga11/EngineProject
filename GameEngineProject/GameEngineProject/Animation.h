#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Animation
{
public:
    void AddAnimation(const std::string& name, const std::vector<int>& frames, float frameTime);
    void SetCurrentAnimation(const std::string& name);

    void Update(float deltaTime);

    int GetCurrentFrame() const;



private:
    struct AnimationData
    {
        std::vector<int> frames;
        float frameDuration;
    };

    std::unordered_map<std::string, AnimationData> animations;
    AnimationData* currentAnimation = nullptr;

    size_t currentFrameIndex = 0; 
    float elapsedTime = 0.0f;     

public: 
    AnimationData GetAnimation();
};

