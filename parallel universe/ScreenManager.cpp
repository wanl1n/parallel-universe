#include "ScreenManager.h"

//a singleton class
ScreenManager* ScreenManager::sharedInstance = nullptr;

ScreenManager* ScreenManager::getInstance() {
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new ScreenManager();
	}

	return sharedInstance;
}

void ScreenManager::initialize()
{
	this->screenMap[Screen::ScreenName::game] = new GameScreen();
	this->screenMap[Screen::ScreenName::loading] = new LoadingScreen();
	this->currentScreen = this->screenMap[Screen::ScreenName::loading];
}

void ScreenManager::loadScreen(Screen::ScreenName screenName)
{
	if (currentScreen->getName() != screenName)
	{
		this->currentScreen->unloadScreen();

		this->currentScreen = this->screenMap[screenName];
		this->currentScreen->loadScreen();
	}
}

ScreenManager::ScreenManager()
{
}
