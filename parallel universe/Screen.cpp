#include "Screen.h"

#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "MoneyCounter.h"
#include "ScreenManager.h"

Screen::Screen(ScreenName name, int* money)
{
	this->name = name;
	this->score = money;
}

Screen::~Screen()
{
}

void Screen::initializeDisplay()
{
	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	objectList.push_back(fpsCounter->getName());

	SpriteObject* coin = new SpriteObject("coin", "coin");
	GameObjectManager::getInstance()->addObject(coin);
	coin->setActive(false);
	coin->setPosition(0, BaseRunner::WINDOW_HEIGHT - 105);
	//coin->setScale(0.7f, 0.7f);
	objectList.push_back(coin->getName());

	// score text
	MoneyCounter* statsObj = new MoneyCounter(this->score);
	GameObjectManager::getInstance()->addObject(statsObj);
	statsObj->setActive(false);
	objectList.push_back(statsObj->getName());
}

void Screen::update(float deltaTime)
{
}

void Screen::processInput()
{
}

void Screen::loadScreen()
{
	for (std::string objectName : objectList)
	{
		AGameObject* gameObject = GameObjectManager::getInstance()->findObjectByName(objectName);
		gameObject->setActive(true);
	}
}

void Screen::unloadScreen()
{
	for (std::string objectName : objectList)
	{
		AGameObject* gameObject = GameObjectManager::getInstance()->findObjectByName(objectName);
		gameObject->setActive(false);
		//delete gameObject;
	}
}

void Screen::onFinishedExecution()
{
}