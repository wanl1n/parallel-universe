#pragma once
#include "AGameObject.h"

class AnimatedObject : public AGameObject
{
public:
    enum AnimName { idle = 0, playing };

    AnimatedObject(String name);
    void initialize();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);

    void incrementFrame();
    void setTexture(sf::Texture* texture);
    void setCurrentFrame(int nCurrentFrame);
    void setAnimation(AnimName animName);
    int random(int min, int max);

private:
    std::unordered_map<AnimName, std::string> animNames;
	std::unordered_map<AnimName, int> animFramesCount;
    AnimName currentAnim;

    int fps = 10;
    float ticks = 0;
};

