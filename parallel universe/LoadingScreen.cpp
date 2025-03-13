#include "LoadingScreen.h"

#include <iostream>

#include "AnimatedObject.h"
#include "AudioManager.h"
#include "BaseRunner.h"
#include "BGObject.h"
#include "Comeowser.h"
#include "GameObjectManager.h"
#include "LoadingText.h"
#include "MathUtils.h"
#include "Plant.h"
#include "Pot.h"
#include "ScreenManager.h"
#include "SpriteObject.h"

LoadingScreen::LoadingScreen() : Screen(ScreenName::loading)
{
}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::initializeDisplay()
{
	this->loadZenGarden();

	AudioManager::getInstance()->playBGM(Screen::loading);

	Screen::initializeDisplay();
}

void LoadingScreen::loadRhythmGame()
{
	BGObject* bgObject = new BGObject("BG");
	GameObjectManager::getInstance()->addObject(bgObject);

	// baseboard
	bongoCat = new Comeowser("Comeowser");
	GameObjectManager::getInstance()->addObject(bongoCat);
	bongoCat->setPosition(0, BaseRunner::WINDOW_HEIGHT / 2 - bongoCat->getHeight() / 2);
	objectList.push_back("Comeowser");

	// notes
	for (int i = 0; i < this->notesCount; i++)
	{
		NoteObject* note = new NoteObject(i, this->noteType[i]);
		this->notes.push_back(note);
		GameObjectManager::getInstance()->addObject(note);
		if (this->noteType[i] < 0)
		{
			note->setPosition(-note->getWidth(), BaseRunner::WINDOW_HEIGHT / 2 + 100 - 80);
		}
		else
			note->setPosition(-note->getWidth(), BaseRunner::WINDOW_HEIGHT / 2 - 100 - 80);
		objectList.push_back(note->getName());
	}

	// score text
	LoadingText* statsObj = new LoadingText(&this->score, &this->result);
	GameObjectManager::getInstance()->addObject(statsObj);
	objectList.push_back(statsObj->getName());
}

void LoadingScreen::loadMeowno()
{
	BGObject* bgObject = new BGObject("BG");
	GameObjectManager::getInstance()->addObject(bgObject);

	catPiano = new AnimatedObject("CatPiano");
	GameObjectManager::getInstance()->addObject(catPiano);
	catPiano->setPosition(BaseRunner::WINDOW_WIDTH / 2 - catPiano->getWidth() / 2, 100.0f);
	objectList.push_back("CatPiano");

	SpriteObject* keebObj = new SpriteObject("Keyboard", "Keyboard");
	GameObjectManager::getInstance()->addObject(keebObj);
	keebObj->setScale(0.07f, 0.07f);
	keebObj->setPosition(BaseRunner::WINDOW_WIDTH / 2 - keebObj->getWidth() * keebObj->getScale().x / 2, 500);
	objectList.push_back("Keyboard");

	AudioManager::getInstance()->loadAudioList(keebObj->getName(), "meowno", true);
}

void LoadingScreen::loadZenGarden()
{
	BGObject* bgObject = new BGObject("zen garden");
	GameObjectManager::getInstance()->addObject(bgObject);
	bgObject->setScale(2.45f, 2.45f);
	bgObject->setPosition(0, -150);
	bgObject->setActive(false);
	objectList.push_back("zen garden");

	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float x = (50 - j * 30) + (200 + j * 10) * i;
			float y = -120 + 230 * j;
			std::string name = "pot" + std::to_string(index);
			Pot* pot = new Pot(name);
			GameObjectManager::getInstance()->addObject(pot);
			pot->setScale(1.8f, 1.8f);
			pot->setPosition(x, y);
			pot->setActive(false);
			objectList.push_back(name);
			pots.push_back(pot);

			index++;
			int plantType = MathUtils::randomInt(0, 1);
			if (plantType == 1)
			{
				std::string plantName = "cattail" + std::to_string(index);
				Plant* plant = new Plant(plantName, "cattail", pot);
				GameObjectManager::getInstance()->addObject(plant);
				plant->setScale(1.8f, 1.8f);
				plant->setPosition(x, y);
				plant->setInitPos(x, y);
				plant->setActive(false);
				objectList.push_back(plantName);
			} else
			{
				std::string plantName = "star" + std::to_string(index);
				Plant* plant = new Plant(plantName, "star", pot);
				GameObjectManager::getInstance()->addObject(plant);
				plant->setScale(1.8f, 1.8f);
				plant->setPosition(x, y);
				plant->setInitPos(x, y);
				plant->setActive(false);
				objectList.push_back(plantName);
			}
		}
	}

	SpriteObject* coin = new SpriteObject("coin", "coin");
	GameObjectManager::getInstance()->addObject(coin);
	coin->setActive(false);
	coin->setPosition(BaseRunner::WINDOW_WIDTH/2 - 100, 100);
	coin->setScale(0.4f, 0.4f);
	objectList.push_back(coin->getName());

	// score text
	LoadingText* statsObj = new LoadingText(&this->score, &this->result);
	GameObjectManager::getInstance()->addObject(statsObj);
	statsObj->setActive(false);
	objectList.push_back(statsObj->getName());

	this->wateringCan = new SpriteObject("watering can","watering can");
	GameObjectManager::getInstance()->addObject(wateringCan);
	wateringCan->setActive(false);
	wateringCan->setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	objectList.push_back(wateringCan->getName());
}

void LoadingScreen::update(float deltaTime)
{
	Screen::update(deltaTime);

	this->ticks += deltaTime;
	if (wateringCan) wateringCan->setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	score = 0;
	for (Pot* pot : pots)
		score += pot->getScore();
	//if (this->ticks > this->timeStamps[nextNoteIndex] - timeOffset && nextNoteIndex < notesCount)
	//{
	//	this->notes[nextNoteIndex]->startMoving(deltaTime);
	//	nextNoteIndex++;
	//}

	//if (nextNoteIndex < notesCount && this->notes[latestNoteHit]->getPosition().x > MAX_THRESHOLD)
	//{
	//	//this->notes[latestNoteHit]->setActive(false);
	//	this->notes[latestNoteHit]->setAnimation(NoteObject::red);
	//	latestNoteHit++;
	//	this->result = "MISS";
	//}
}

void LoadingScreen::processInput()
{
	Screen::processInput();
	
	//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) &&
	//	!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	//{
	//	inputFrames = 0;
	//	bongoCat->setAnimation(Comeowser::idle);
	//}

	//// todo : input audio
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	//{
	//	bongoCat->setAnimation(Comeowser::up);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	//{
	//	bongoCat->setAnimation(Comeowser::down);
	//}

	//if (latestNoteHit < nextNoteIndex)
	//{
	//	NoteObject* currentNote = this->notes[latestNoteHit];
	//	int currentType = this->noteType[latestNoteHit];

	//	// note type = 1; up
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && inputFrames == 0)
	//	{
	//		if (currentType == 1 &&
	//			currentNote->getPosition().x > MIN_THRESHOLD &&
	//			currentNote->getPosition().x <= MAX_THRESHOLD)
	//		{
	//			score++;
	//			result = "HIT";
	//			currentNote->setAnimation(NoteObject::pop);
	//		} else
	//		{
	//			result = "MISS";
	//			currentNote->setAnimation(NoteObject::red);
	//		}
	//		latestNoteHit++;
	//		//currentNote->setActive(false);

	//		inputFrames++;
	//	}

	//	// note type = -1; down
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && inputFrames == 0)
	//	{
	//		if (currentType == -1 &&
	//			currentNote->getPosition().x > MIN_THRESHOLD &&
	//			currentNote->getPosition().x <= MAX_THRESHOLD)
	//		{
	//			score++;
	//			result = "HIT";
	//			currentNote->setAnimation(NoteObject::pop);
	//		}
	//		else
	//		{
	//			result = "MISS";
	//			currentNote->setAnimation(NoteObject::red);
	//		}
	//		latestNoteHit++;
	//		//currentNote->setActive(false);

	//		inputFrames++;
	//	}

	//	// first in note
	//	sf::Keyboard::Key key = sf::Keyboard::Key::Up;
	//	if (this->noteType[latestNoteHit] < 0)
	//		key = sf::Keyboard::Key::Down;
	//}

	//if (AudioManager::getInstance()->isPlayingSFX())
	//	catPiano->setAnimation(AnimatedObject::playing);
	//else
	//	catPiano->setAnimation(AnimatedObject::idle);

	//// Meow notes
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a0);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp0);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b0);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::csharp1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::d1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::dsharp1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::e1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::f1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::fsharp1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::g1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::gsharp1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b1);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::csharp2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::d2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::dsharp2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::e2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::f2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::fsharp2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::g2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::gsharp2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::a2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::asharp2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Comma))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::b2);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
	//	AudioManager::getInstance()->playSFX("Keyboard meowno", AudioManager::MeowNotes::c3);
}

void LoadingScreen::onFinishedExecution()
{
	std::cout << "Finished loading Loading Screen." << std::endl;
}
