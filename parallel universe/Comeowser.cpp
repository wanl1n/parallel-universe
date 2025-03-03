#include "Comeowser.h"

#include <random>

#include "TextureManager.h"


Comeowser::Comeowser(std::string name)
    : AGameObject(name)
{
    this->animNames[idle] = "idle";
    this->animNames[up] = "up";
    this->animNames[down] = "down";

    this->animFramesCount[idle] = 1;
    this->animFramesCount[up] = 1;
    this->animFramesCount[down] = 1;

    this->currentAnim = idle;
}

void Comeowser::initialize()
{
    TextureManager::getInstance()->loadSpriteSheets(name, animNames[idle]);
    TextureManager::getInstance()->loadSpriteSheets(name, animNames[up]);
    TextureManager::getInstance()->loadSpriteSheets(name, animNames[down]);

    //assign texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name + " " + animNames[idle], 0);
    this->setTexture(texture);
}

void Comeowser::update(sf::Time deltaTime)
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name + " " + animNames[currentAnim], 0);
    this->setTexture(texture);
}

void Comeowser::processInput(sf::Event event)
{
}

void Comeowser::setTexture(sf::Texture* texture)
{
    this->sprite = new sf::Sprite(*texture);
    this->sprite->setTexture(*texture);
}

void Comeowser::setAnimation(AnimName animName)
{
    this->currentAnim = animName;
}

int Comeowser::random(int min, int max)
{
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    return distrib(gen);
}
