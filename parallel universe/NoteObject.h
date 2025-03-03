#pragma once
#include "SpriteObject.h"

class NoteObject : public SpriteObject
{
public:
	NoteObject(int type);
	~NoteObject();

	void initialize() override;
	void update(sf::Time deltaTime) override;

	void startMoving(float deltaTime)
	{
		this->active = true;
		this->moving = true;
	}

private:
	const float MAX_THRESHOLD = 1600.0f;
	int type;
	sf::Keyboard::Key inputType;
	bool moving = false;
};

