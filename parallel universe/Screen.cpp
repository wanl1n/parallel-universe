#include "Screen.h"

#include "GameObjectManager.h"

Screen::Screen(ScreenName name)
{
	this->name = name;
}

Screen::~Screen()
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
