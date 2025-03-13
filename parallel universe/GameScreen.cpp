#include "GameScreen.h"

#include <iostream>

#include "AudioManager.h"
#include "BaseRunner.h"
#include "Cutscene.h"
#include "GameObjectManager.h"
#include "ScreenManager.h"
#include "Threading/SceneLoader.h"

GameScreen::GameScreen() : Screen(game)
{
}

GameScreen::~GameScreen() {}

void GameScreen::initializeDisplay()
{
	cs = new Cutscene("Tutorial");
	GameObjectManager::getInstance()->addObject(cs);
	cs->setActive(false);
	objectList.push_back(cs->getName());
	cs->setScale(2.f, 2.f);
	/*display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);
	display->setActive(false);
	objectList.push_back("TextureDisplay");*/

	Screen::initializeDisplay();
}

void GameScreen::loadScreen()
{
	AudioManager::getInstance()->playBGM(Screen::ScreenName::game);

	Screen::loadScreen();
}

void GameScreen::update(float deltaTime)
{
	Screen::update(deltaTime);

	cs->setPosition(BaseRunner::WINDOW_WIDTH/2 - cs->getWidth(), BaseRunner::WINDOW_HEIGHT/2 - cs->getHeight());
}

void GameScreen::processInput()
{
	Screen::processInput();
	this->load = this->cs->isLoading();
}

void GameScreen::onFinishedExecution()
{
}