#include "LoadingText.h"
#include <iostream>
#include "BaseRunner.h"

LoadingText::LoadingText(int* score, std::string* result) : AGameObject("LoadingText")
{
	this->score = score;
	this->result = result;
}

LoadingText::~LoadingText()
{
	delete this->statsText;
	delete this->resultText;
	AGameObject::~AGameObject();
}

void LoadingText::initialize()
{
	sf::Font* font = new sf::Font();
	font->openFromFile("Media/Bellefair.otf");

	this->statsText = new sf::Text(*font);
	this->statsText->setFont(*font);
	this->statsText->setPosition(sf::Vector2f(BaseRunner::WINDOW_WIDTH/2, 100));
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.0f);
	this->statsText->setCharacterSize(35);

	this->resultText = new sf::Text(*font);
	this->resultText->setFont(*font);
	this->resultText->setPosition(sf::Vector2f(BaseRunner::WINDOW_WIDTH / 2 - 30, 150));
	this->resultText->setOutlineColor(sf::Color(1.0f, 0.4f, 0.5f));
	this->resultText->setOutlineThickness(2.0f);
	this->resultText->setCharacterSize(35);
}

void LoadingText::processInput(sf::Event event)
{
}

void LoadingText::update(sf::Time deltaTime)
{
	this->updateScore();

	if (!this->result->empty()) timer += deltaTime.asSeconds();
	if (this->result->empty()) timer = 0;
	if (timer > 1.0f) *this->result = " ";
}

void LoadingText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->statsText != nullptr)
		targetWindow->draw(*this->statsText);

	if (this->resultText != nullptr)
		targetWindow->draw(*this->resultText);
}

void LoadingText::updateScore()
{
	sf::String fpsString = std::to_string(*this->score);
	this->statsText->setString(fpsString);
	this->resultText->setString(*result);
}