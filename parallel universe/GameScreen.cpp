#include "GameScreen.h"

#include <iostream>

#include "AudioManager.h"
#include "GameObjectManager.h"
#include "ScreenManager.h"
#include "Threading/SceneLoader.h"

GameScreen::GameScreen() : Screen(game)
{
}

GameScreen::~GameScreen() {}

void GameScreen::initializeDisplay()
{
	/*display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);
	display->setActive(false);
	objectList.push_back("TextureDisplay");*/

	Screen::initializeDisplay();
}

void GameScreen::processInput()
{
	Screen::processInput();
	//this->load = this->display->isLoading();

	if (!AudioManager::getInstance()->isPlayingBGM())
		AudioManager::getInstance()->playBGM(Screen::ScreenName::game);
}

void GameScreen::onFinishedExecution()
{
}