#include "Screen.h"

#include "GameObjectManager.h"
#include "ScreenManager.h"

Screen::Screen(ScreenName name)
{
	this->name = name;
}

Screen::~Screen()
{
}

void Screen::initializeDisplay()
{
	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	objectList.push_back(fpsCounter->getName());
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