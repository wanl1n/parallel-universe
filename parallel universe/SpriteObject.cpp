#include "SpriteObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

SpriteObject::SpriteObject(String name) : AGameObject(name) {}

void SpriteObject::initialize()
{
	//assign texture
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->name, 0);

	this->sprite = new sf::Sprite(*texture);
	this->sprite->setTexture(*texture);
}

void SpriteObject::processInput(sf::Event event)
{
}

void SpriteObject::update(sf::Time deltaTime)
{
}

sf::Sprite* SpriteObject::getSprite()
{
	return this->sprite;
}