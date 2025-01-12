#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex): AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	//assign texture
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	this->sprite = new sf::Sprite(*texture);
	this->sprite->setTexture(*texture);
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
