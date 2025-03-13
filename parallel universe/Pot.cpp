#include "Pot.h"

#include "AudioManager.h"
#include "TextureManager.h"

Pot::Pot(String name) : AGameObject(name) {}

Pot::~Pot()
{
	delete this->unwatered;
	delete this->watered;
}

void Pot::initialize()
{
	unwatered = TextureManager::getInstance()->getFromTextureMap("pot", 0);
	watered = TextureManager::getInstance()->getFromTextureMap("pot_watered", 0);
	this->sprite = new sf::Sprite(*unwatered);
	this->sprite->setTexture(*unwatered);

	AudioManager::getInstance()->loadAudioList(name, "zen", true);
}

void Pot::processInput(sf::Event event)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	if (sprite->getGlobalBounds().contains(mousePos))
		water();
}

void Pot::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asSeconds();
	if (ticks > dryingTime)
	{
		this->ticks = 0;
		this->dry = true;
		this->sprite->setTexture(*unwatered);
	}
}

void Pot::water()
{
	if (dry)
	{
		this->ticks = 0;
		this->dry = false;
		this->sprite->setTexture(*watered);
		AudioManager::getInstance()->playSFX(name + " zen", 1);
		score++;
	}
}
