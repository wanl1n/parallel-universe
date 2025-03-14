#include "LoadingText.h"
#include <iostream>
#include "BaseRunner.h"

LoadingText::LoadingText() : AGameObject("LoadingText") {}

LoadingText::~LoadingText()
{
	delete this->messageText;
	AGameObject::~AGameObject();
}

void LoadingText::initialize()
{
	sf::Font* font = new sf::Font();
	font->openFromFile("Media/SeriesOrbit.TTF");

	this->messageText = new sf::Text(*font);
	this->messageText->setFont(*font);
	this->messageText->setPosition(sf::Vector2f(20, 20));
	this->messageText->setFillColor(sf::Color::White);
	this->messageText->setOutlineThickness(4.0f);
	this->messageText->setCharacterSize(25);
	this->messageText->setString("Water the plants by moving your mouse around and earn extra coins!");
}

void LoadingText::processInput(sf::Event event)
{
}

void LoadingText::update(sf::Time deltaTime)
{
}

void LoadingText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->messageText != nullptr)
		targetWindow->draw(*this->messageText);
}