#include "Animation.h"
#include <unordered_map>
#include <vector>
#include <string>

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

AnimationData Animation::GetAnimation()
{
    return currentAnimation;
}
