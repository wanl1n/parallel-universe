#pragma once
#include "AGameObject.h"
#include "Pot.h"
#include "SpriteObject.h"

class Plant : public AGameObject
{
public:
    enum AnimName { idle = 0 };

    Plant(String name, std::string objName, Pot* pot);
    void initialize();
    void processInput(sf::Event event) override;
    void bounce(float deltaTime);
    void update(sf::Time deltaTime) override;

    void incrementFrame();
    void setTexture(sf::Texture* texture);
    void setCurrentFrame(int nCurrentFrame);
    void setAnimation(AnimName animName);

    void blink(float deltaTime);
    void setInitPos(float x, float y);

protected:
    std::unordered_map<AnimName, std::string> animNames;
	std::unordered_map<AnimName, int> animFramesCount;
    AnimName currentAnim;
    std::string objName;
    int fps = 3;
    float ticks = 0;
    float blinkTimer = 0;
    float blinkInterval = 4;
    int frameIndex = 0;
    bool blinking = false;
    bool openingEyes = false;

    // bounce
    sf::Vector2f initPos;
    float xOffset = 5.0f;
    float yOffset = 2.0f;
    bool movingRight = true;
    bool movingUp = false;

    Pot* pot;
    SpriteObject* needWater;
};
