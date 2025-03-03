#include "ScreenManager.h"

#include <iostream>

#include "Threading/SceneLoader.h"

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
	this->threadPool = new ThreadPool("Texture Manager Thread Pool", 1);
	this->threadPool->startScheduler();

	this->screenMap[Screen::ScreenName::loading] = new LoadingScreen();
	GameScreen* gs = new GameScreen();
	this->screenMap[Screen::ScreenName::game] = gs;
	SceneLoader* loader = new SceneLoader(Screen::game, gs);
	this->threadPool->scheduleTask(loader);

	this->currentScreen = this->screenMap[Screen::ScreenName::loading];
}

void ScreenManager::addScreen(Screen::ScreenName screenName, Screen* screen)
{
	this->screenMap[screenName] = screen;
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

void ScreenManager::processInput()
{
	this->currentScreen->processInput();
}

void ScreenManager::update(float deltaTime)
{
	this->currentScreen->update(deltaTime);
}

ScreenManager::ScreenManager()
{
}
