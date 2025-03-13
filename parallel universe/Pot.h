#pragma once
#include "AGameObject.h"

class Pot : public AGameObject
{
public:
	Pot(String name);
	~Pot();
	void initialize();

	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;

	bool isDry() { return dry; }
	int getScore() { return score; }
	void water();

private:
	sf::Texture* unwatered;
	sf::Texture* watered;

	bool dry = true;
	float ticks = 0;
	float dryingTime = 3.0f;
	int score = 0;
};

