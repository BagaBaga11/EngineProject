#pragma once
#include <unordered_map>
#include <vector>
#include <string>

    struct AnimationData
    {
        std::vector<int> frames;
        float frameDuration;
    };

class Animation
{
public:
    void AddAnimation(const std::string& name, const std::vector<int>& frames, float frameTime);
    void SetCurrentAnimation(const std::string& name);

    void Update(float deltaTime);

    int GetCurrentFrame() const;
    void SetStopFrame(int frame);


private:


    std::unordered_map<std::string, AnimationData> animations;
    AnimationData* currentAnimation = nullptr;

    size_t currentFrameIndex = 0; 
    float elapsedTime = 0.0f;     

    int stopFrame = -1;

public: 
    std::vector<int> GetAnimation(const std::string& anim);
};

