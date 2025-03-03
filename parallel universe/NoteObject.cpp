#include "NoteObject.h"

#include "Comeowser.h"

NoteObject::NoteObject(int type) : SpriteObject("MeowNote")
{
	this->type = type;
	if (type == -1) this->inputType = sf::Keyboard::Key::Up;
	else if (type == 1) this->inputType = sf::Keyboard::Key::Down;
}

NoteObject::~NoteObject()
{
}

void NoteObject::initialize()
{
	SpriteObject::initialize();

	this->setScale(0.5f, 0.5f);
	this->active = false;
}

void NoteObject::update(sf::Time deltaTime)
{
	SpriteObject::update(deltaTime);

	if (moving)
	{
		float speed = 120.0f;
		this->setPosition(this->posX + speed * deltaTime.asSeconds(),
							this->posY);
	}
}