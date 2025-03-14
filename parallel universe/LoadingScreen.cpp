#include "LoadingScreen.h"

#include <iostream>

#include "AudioManager.h"
#include "BaseRunner.h"
#include "BGObject.h"
#include "GameObjectManager.h"
#include "MathUtils.h"
#include "Plant.h"
#include "Pot.h"
#include "ScreenManager.h"
#include "SpriteObject.h"

LoadingScreen::LoadingScreen(int* score) : Screen(ScreenName::loading, score)
{
}
LoadingScreen::~LoadingScreen() {}

void LoadingScreen::initializeDisplay()
{
	this->loadZenGarden();

	AudioManager::getInstance()->playBGM(Screen::loading);

	Screen::initializeDisplay();
}

void LoadingScreen::loadZenGarden()
{
	BGObject* bgObject = new BGObject("zen garden");
	GameObjectManager::getInstance()->addObject(bgObject);
	bgObject->setScale(2.45f, 2.45f);
	bgObject->setPosition(0, -150);
	bgObject->setActive(false);
	objectList.push_back("zen garden");
	objects.push_back(bgObject);

	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float x = (150 - j * 30) + (200 + j * 10) * i;
			float y = 50 + 230 * j;
			std::string name = "pot" + std::to_string(index);
			Pot* pot = new Pot(name);
			GameObjectManager::getInstance()->addObject(pot);
			pot->setActive(false);
			pot->setScale(1.8f, 1.8f);
			pot->setPosition(x, y);
			objectList.push_back(name);
			objects.push_back(pot);
			pots.push_back(pot);

			index++;
			int plantType = MathUtils::randomInt(0, 1);
			if (plantType == 1)
			{
				std::string plantName = "cattail" + std::to_string(index);
				Plant* plant = new Plant(plantName, "cattail", pot);
				GameObjectManager::getInstance()->addObject(plant);
				plant->setActive(false);
				plant->setScale(1.8f, 1.8f);
				plant->setPosition(x, y);
				plant->setInitPos(x, y);
				objectList.push_back(plantName);
				objects.push_back(plant);
			} else
			{
				std::string plantName = "star" + std::to_string(index);
				Plant* plant = new Plant(plantName, "star", pot);
				GameObjectManager::getInstance()->addObject(plant);
				plant->setActive(false);
				plant->setScale(1.8f, 1.8f);
				plant->setPosition(x, y);
				plant->setInitPos(x, y);
				objectList.push_back(plantName);
				objects.push_back(plant);
			}
		}
	}

	message = new LoadingText();
	GameObjectManager::getInstance()->addObject(message);
	message->setActive(false);
	objectList.push_back(message->getName());

	// for transition
	bungee = new SpriteObject("bungee", "bungee");
	GameObjectManager::getInstance()->addObject(bungee);
	bungee->setPosition(BaseRunner::WINDOW_WIDTH/2 - bungee->getWidth()*2.8f/2, -1500);
	bungee->setScale(2.8f, 2.8f);
	objectList.push_back(bungee->getName());
	objects.push_back(bungee);

	this->wateringCan = new SpriteObject("watering can","watering can");
	GameObjectManager::getInstance()->addObject(wateringCan);
	wateringCan->setActive(false);
	wateringCan->setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	objectList.push_back(wateringCan->getName());
	objects.push_back(wateringCan);

	AudioManager::getInstance()->loadAudioList("Loading", "zen", true);
}

void LoadingScreen::update(float deltaTime)
{
	Screen::update(deltaTime);

	this->ticks += deltaTime;
	if (wateringCan) wateringCan->setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	*score = 0;
	for (Pot* pot : pots)
		*score += pot->getScore();

	if (!ScreenManager::getInstance()->loadingProgress())
		transitioning = true;

	if (transitioning)
	{
		if (!screamed)
			AudioManager::getInstance()->playSFX("Loading zen", 1);

		if (bungee->getPosition().y < -100)
		{
			bungeeSpeed += 50;
			bungee->setActive(true);
			sf::Vector2f newPos = MathUtils::interpolateTowards( bungee->getPosition(), sf::Vector2f(BaseRunner::WINDOW_WIDTH / 2 - bungee->getWidth() * 2.8f / 2, -100), bungeeSpeed * deltaTime);
			bungee->setPosition(newPos.x, newPos.y);

			if (newPos.y >= -100)
				pulled = true;
		}

		if (pulled)
		{
			message->setActive(false);
			for (AGameObject* obj : objects)
			{
				bungeeSpeed += 50;
				sf::Vector2f targetPos = sf::Vector2f(obj->getPosition().x, -1500);
				sf::Vector2f newPos = MathUtils::interpolateTowards(obj->getPosition(), targetPos, bungeeSpeed * deltaTime);
				obj->setPosition(newPos.x, newPos.y);
			}

			if (objects[objects.size()-1]->getPosition().y <= -1500)
				ready = true;
		}
	}

	transition();
}

void LoadingScreen::transition()
{
	if (ready)
		ScreenManager::getInstance()->loadScreen(Screen::game);
}

void LoadingScreen::onFinishedExecution()
{
	//std::cout << "Finished loading Loading Screen." << std::endl;
}
