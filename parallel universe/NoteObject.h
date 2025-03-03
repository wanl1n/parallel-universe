#pragma once
#include "SpriteObject.h"

class NoteObject : public AGameObject
{
public:
	enum AnimName { idle = 0, pop, red };

	NoteObject(int index, int type);
	~NoteObject();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;

	void incrementFrame();
	void setTexture(sf::Texture* texture);
	void setCurrentFrame(int nCurrentFrame);
	void setAnimation(AnimName animName);
	int random(int min, int max);

	void startMoving(float deltaTime)
	{
		this->active = true;
		this->moving = true;
	}

	sf::Sprite* getSprite()
	{
		return this->sprite;
	}

private:
	const float MAX_THRESHOLD = 1700.0f;

	std::unordered_map<AnimName, std::string> animNames;
	std::unordered_map<AnimName, int> animFramesCount;
	AnimName currentAnim;

	int type;
	bool moving = false;
};

