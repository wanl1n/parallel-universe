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
	}
}

void Screen::onFinishedExecution()
{
}