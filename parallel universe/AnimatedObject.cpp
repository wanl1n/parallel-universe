#include "AnimatedObject.h"

#include <random>

#include "TextureManager.h"


AnimatedObject::AnimatedObject(std::string name)
	: AGameObject(name)
{
    this->animNames[idle] = "idle";
    this->animNames[playing] = "playing";

    this->animFramesCount[idle] = 2;
    this->animFramesCount[playing] = 31;

	this->currentAnim = idle;
    this->initialize();
}

void AnimatedObject::initialize()
{
	TextureManager::getInstance()->loadSpriteSheets(name, animNames[idle]);
	TextureManager::getInstance()->loadSpriteSheets(name, animNames[playing]);

    //assign texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name + " " + animNames[idle], 0);
    this->setTexture(texture);
}

void AnimatedObject::processInput(sf::Event event)
{
}

void AnimatedObject::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asSeconds();
    if (this->ticks > 1.0f / this->fps)
    {
        this->ticks = 0;
        this->incrementFrame();
    }
}

void AnimatedObject::incrementFrame() {
    int frameIndex = random(0, this->animFramesCount[currentAnim]);
    this->setCurrentFrame(frameIndex);
}

void AnimatedObject::setTexture(sf::Texture* texture)
{
    float textureWidth = texture->getSize().x;
    float textureHeight = texture->getSize().y;
    float scaleX = textureWidth / 168.0f;
    float scaleY = textureHeight / 168.0f;

    this->sprite = new sf::Sprite(*texture);
    this->sprite->setTexture(*texture);
    this->sprite->setScale(sf::Vector2f(scaleX, scaleY));
}

void AnimatedObject::setCurrentFrame(int nCurrentFrame) {
	sf::Texture* frame = TextureManager::getInstance()->getFromTextureMap(this->name + " " + this->animNames[currentAnim], nCurrentFrame);
    this->setTexture(frame);
}

void AnimatedObject::setAnimation(AnimName animName)
{
    this->currentAnim = animName;
}

int AnimatedObject::random(int min, int max)
{
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    return distrib(gen);
}
