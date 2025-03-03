#pragma once
#include "AGameObject.h"

class Comeowser : public AGameObject
{
public:
    enum AnimName { idle = 0, up, down };

    Comeowser(String name);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void processInput(sf::Event event) override;

    void setTexture(sf::Texture* texture);
    void setCurrentFrame(int nCurrentFrame);
    void setAnimation(AnimName animName);
    int random(int min, int max);

protected:
    std::unordered_map<AnimName, std::string> animNames;
    std::unordered_map<AnimName, int> animFramesCount;
    AnimName currentAnim;

    int fps = 1;
    float ticks = 0;
};

