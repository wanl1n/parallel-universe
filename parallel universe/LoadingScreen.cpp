#include "LoadingScreen.h"

#include "AnimatedObject.h"
#include "GameObjectManager.h"

LoadingScreen::LoadingScreen() : Screen(ScreenName::loading)
{
	AnimatedObject* catPiano = new AnimatedObject("CatPiano");
	GameObjectManager::getInstance()->addObject(catPiano);

	objectList.push_back("CatPiano");
}

LoadingScreen::~LoadingScreen() {}