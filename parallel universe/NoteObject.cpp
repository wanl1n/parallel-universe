#include "NoteObject.h"

#include <random>

#include "TextureManager.h"

NoteObject::NoteObject(int index, int type) 
	: AGameObject("MeowNote" + std::to_string(index))
{
	this->animNames[idle] = "idle";
	this->animNames[pop] = "pop";
	this->animNames[red] = "red";

	this->animFramesCount[idle] = 1;
	this->animFramesCount[pop] = 1;
	this->animFramesCount[red] = 1;

	this->currentAnim = idle;
}

NoteObject::~NoteObject()
{
}

void NoteObject::initialize()
{
	TextureManager::getInstance()->loadSpriteSheets("MeowNote", animNames[idle]);
	TextureManager::getInstance()->loadSpriteSheets("MeowNote", animNames[pop]);
	TextureManager::getInstance()->loadSpriteSheets("MeowNote", animNames[red]);

	//assign texture
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("MeowNote " + animNames[idle], 0);
	this->setTexture(texture);

	this->setScale(0.3f, 0.3f);
	this->sprite->setOrigin(sf::Vector2f(this->getWidth()/2, this->getHeight() / 2));
	this->active = false;
}

void NoteObject::processInput(sf::Event event)
{
}

void NoteObject::update(sf::Time deltaTime)
{
	this->sprite->setOrigin(sf::Vector2f(this->getWidth() / 2, this->getHeight() / 2));
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("MeowNote " + animNames[currentAnim], 0);
	this->setTexture(texture);

	if (moving)
	{
		float speed = 200.0f;
		this->setPosition(this->posX + speed * deltaTime.asSeconds(),
							this->posY);
	}
}

void NoteObject::setTexture(sf::Texture* texture)
{
	this->sprite = new sf::Sprite(*texture);
	this->sprite->setTexture(*texture);
}

void NoteObject::setCurrentFrame(int nCurrentFrame)
{
	sf::Texture* frame = TextureManager::getInstance()->getFromTextureMap(this->name + " " + this->animNames[currentAnim], nCurrentFrame);
	this->setTexture(frame);
}

void NoteObject::setAnimation(AnimName animName)
{
	this->currentAnim = animName;
}

int NoteObject::random(int min, int max)
{
	// Initialize a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	// Generate random number in the range [min, max]
	return distrib(gen);
}
