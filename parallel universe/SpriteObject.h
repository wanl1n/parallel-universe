#pragma once
#include "AGameObject.h"

class SpriteObject : public AGameObject
{
public:
	SpriteObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	sf::Sprite* getSprite();
};

