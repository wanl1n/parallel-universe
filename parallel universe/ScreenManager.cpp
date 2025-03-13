#include "ScreenManager.h"

#include <iostream>

#include "TitleScreen.h"
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

	TitleScreen* ts = new TitleScreen();
	this->screenMap[Screen::ScreenName::main] = ts;

	LoadingScreen* ls = new LoadingScreen();
	this->screenMap[Screen::ScreenName::loading] = ls;
	SceneLoader* loadingLoader = new SceneLoader(Screen::loading, ls);
	this->threadPool->scheduleTask(loadingLoader);

	GameScreen* gs = new GameScreen();
	this->screenMap[Screen::ScreenName::game] = gs;
	SceneLoader* gameLoader = new SceneLoader(Screen::game, gs);
	this->threadPool->scheduleTask(gameLoader);

	this->currentScreen = this->screenMap[Screen::ScreenName::main];
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

	if (currentScreen == this->screenMap[Screen::ScreenName::loading] && 
		!this->screenMap[Screen::ScreenName::game]->isLoading())
		ScreenManager::getInstance()->loadScreen(Screen::game);
}

ScreenManager::ScreenManager()
{
}
