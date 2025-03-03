#pragma once
#include "AGameObject.h"
class LoadingText : public AGameObject
{
public:
	LoadingText(int* score, std::string* result);
	~LoadingText();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	int* score;
	std::string* result;
	sf::Text* statsText;
	sf::Text* resultText;

	float timer = 0;

	void updateScore();

};