#include "TitleScreen.h"

#include "AudioManager.h"
#include "BGObject.h"
#include "GameObjectManager.h"
#include "ScreenManager.h"

TitleScreen::TitleScreen() : Screen(ScreenName::main)
{
	BGObject* mainmenuBG = new BGObject("Main Menu BG");
	GameObjectManager::getInstance()->addObject(mainmenuBG);
	objectList.push_back("Main Menu BG");
	//AudioManager::getInstance()->playBGM(Screen::main);
}


void TitleScreen::update(float deltaTime)
{
	Screen::update(deltaTime);
}

void TitleScreen::processInput()
{
	Screen::processInput();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		ScreenManager::getInstance()->loadScreen(loading);
}
