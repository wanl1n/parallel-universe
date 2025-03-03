#include "LoadingScreen.h"

#include <iostream>

#include "AnimatedObject.h"
#include "AudioManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "ScreenManager.h"
#include "SpriteObject.h"

LoadingScreen::LoadingScreen() : Screen(ScreenName::loading)
{
	std::cout << "Loading Screen initializing" << std::endl;

	catPiano = new AnimatedObject("CatPiano");
	GameObjectManager::getInstance()->addObject(catPiano);
	catPiano->setPosition(BaseRunner::WINDOW_WIDTH / 2 - catPiano->getWidth()/2, 100.0f);

	SpriteObject* keebObj = new SpriteObject("Keyboard");
	GameObjectManager::getInstance()->addObject(keebObj);
	keebObj->setScale(0.07f, 0.07f);
	keebObj->setPosition(BaseRunner::WINDOW_WIDTH / 2 - keebObj->getWidth() * keebObj->getScale().x / 2, 500);

	AudioManager::getInstance()->loadAudioList(keebObj->getName(), "meowno", true);

	objectList.push_back("CatPiano");
	objectList.push_back("Keyboard");

	std::cout << "Loading Screen initialized" << std::endl;
}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::processInput()
{
	Screen::processInput();

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		ScreenManager::getInstance()->loadScreen(Screen::ScreenName::game);*/

	if (AudioManager::getInstance()->isPlayingSFX())
		catPiano->setAnimation(AnimatedObject::playing);
	else
		catPiano->setAnimation(AnimatedObject::idle);

	// Meow notes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::csharp1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::d1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::dsharp1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::e1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::f1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::fsharp1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::g1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::gsharp1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::csharp2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::d2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::dsharp2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::e2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::f2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::fsharp2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::g2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::gsharp2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Comma))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c3);
}
