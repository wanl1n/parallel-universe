#include "MoneyCounter.h"
#include <iostream>
#include "BaseRunner.h"

MoneyCounter::MoneyCounter(int* money) : AGameObject("MoneyCounter")
{
	this->money = money;
}

MoneyCounter::~MoneyCounter()
{
	delete this->moneyText;
	AGameObject::~AGameObject();
}

void MoneyCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->openFromFile("Media/SeriesOrbit.TTF");

	this->moneyText = new sf::Text(*font);
	this->moneyText->setFont(*font);
	this->moneyText->setPosition(sf::Vector2f(200, BaseRunner::WINDOW_HEIGHT - 50));
	this->moneyText->setFillColor(sf::Color(181, 253, 92));
	this->moneyText->setCharacterSize(35);
}

void MoneyCounter::processInput(sf::Event event)
{
}

void MoneyCounter::update(sf::Time deltaTime)
{
	this->updateScore();
}

void MoneyCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->moneyText != nullptr)
		targetWindow->draw(*this->moneyText);
}

void MoneyCounter::updateScore()
{
	sf::String fpsString = std::to_string(*this->money);
	this->moneyText->setString(fpsString);
}