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

	float textureWidth = texture->getSize().x;
	float textureHeight = texture->getSize().y;
	float scaleX = textureWidth / 168.0f;
	float scaleY = textureHeight / 168.0f;

	this->sprite = new sf::Sprite(*texture);
	this->sprite->setTexture(*texture);
	this->sprite->setScale(sf::Vector2f(scaleX, scaleY));
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
