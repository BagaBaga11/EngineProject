#include "Animation.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

void Animation::AddAnimation(const std::string& name, const std::vector<int>& frames, float frameTime)
{
    animations[name] = { frames, frameTime };
}

void Animation::SetCurrentAnimation(const std::string& name)
{
    if (animations.find(name) != animations.end())
    {
        currentAnimation = &animations[name];
        currentFrameIndex = 0;
        elapsedTime = 0.0f;
    }
}

void Animation::Update(float deltaTime)
{
    if (!currentAnimation)
        return;

    elapsedTime += deltaTime;
    if (elapsedTime >= currentAnimation->frameDuration) 
    {
        elapsedTime = 0.0f;

        if (stopFrame >= 0 && currentFrameIndex == stopFrame) {
            return;
        }
        currentFrameIndex = (currentFrameIndex + 1) % currentAnimation->frames.size();
    }
}

int Animation::GetCurrentFrame() const
{
    if (!currentAnimation)
    {
        return 0.0f;
    }
    else
    {
        return currentAnimation->frames[currentFrameIndex];
    }
}

void Animation::SetStopFrame(int frame)
{
    stopFrame = frame;
}

std::vector<int> Animation::GetAnimation(const std::string& anim)
{
    if (!anim.empty())
    {
        auto it = animations.find(anim);
        if (it != animations.end())
        {
            return it->second.frames;
        }
    }
    
    if (currentAnimation)
    {
        return currentAnimation->frames;
    }
    return {};
}
