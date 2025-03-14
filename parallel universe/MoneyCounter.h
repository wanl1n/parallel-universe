#pragma once
#include "AGameObject.h"
class MoneyCounter : public AGameObject
{
public:
	MoneyCounter(int* money);
	~MoneyCounter();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	int* money;
	sf::Text* moneyText;

	void updateScore();
};