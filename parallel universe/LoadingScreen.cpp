#include "LoadingScreen.h"

#include <iostream>

#include "AnimatedObject.h"
#include "AudioManager.h"
#include "BaseRunner.h"
#include "Comeowser.h"
#include "GameObjectManager.h"
#include "LoadingText.h"
#include "ScreenManager.h"
#include "SpriteObject.h"

LoadingScreen::LoadingScreen() : Screen(ScreenName::loading)
{
	catPiano = new AnimatedObject("CatPiano");
	GameObjectManager::getInstance()->addObject(catPiano);
	catPiano->setPosition(BaseRunner::WINDOW_WIDTH / 2 - catPiano->getWidth()/2, 100.0f);
	objectList.push_back("CatPiano");

	SpriteObject* keebObj = new SpriteObject("Keyboard");
	GameObjectManager::getInstance()->addObject(keebObj);
	keebObj->setScale(0.07f, 0.07f);
	keebObj->setPosition(BaseRunner::WINDOW_WIDTH / 2 - keebObj->getWidth() * keebObj->getScale().x / 2, 500);
	objectList.push_back("Keyboard");

	// rhythm game
	// baseboard
	bongoCat = new Comeowser("Comeowser");
	GameObjectManager::getInstance()->addObject(bongoCat);
	bongoCat->setPosition(0, BaseRunner::WINDOW_HEIGHT / 2 - bongoCat->getHeight()/2);
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
		} else
			note->setPosition(-note->getWidth(), BaseRunner::WINDOW_HEIGHT / 2 - 100 - 80);
		objectList.push_back(note->getName());
	}
	// score text
	LoadingText* statsObj = new LoadingText(&this->score, &this->result);
	GameObjectManager::getInstance()->addObject(statsObj);
	objectList.push_back(statsObj->getName());

	AudioManager::getInstance()->loadAudioList(keebObj->getName(), "meowno", true);
	AudioManager::getInstance()->playBGM(Screen::loading);
}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::update(float deltaTime)
{
	Screen::update(deltaTime);

	this->ticks += deltaTime;
	if (this->ticks > this->timeStamps[nextNoteIndex] - timeOffset && nextNoteIndex < notesCount)
	{
		this->notes[nextNoteIndex]->startMoving(deltaTime);
		nextNoteIndex++;
	}

	if (nextNoteIndex < notesCount && this->notes[latestNoteHit]->getPosition().x > MAX_THRESHOLD)
	{
		//this->notes[latestNoteHit]->setActive(false);
		this->notes[latestNoteHit]->setAnimation(NoteObject::red);
		latestNoteHit++;
		this->result = "MISS";
	}
}

void LoadingScreen::processInput()
{
	Screen::processInput();
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		inputFrames = 0;
		bongoCat->setAnimation(Comeowser::idle);
	}

	// todo : input audio
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		bongoCat->setAnimation(Comeowser::up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		bongoCat->setAnimation(Comeowser::down);
	}

	if (latestNoteHit < nextNoteIndex)
	{
		NoteObject* currentNote = this->notes[latestNoteHit];
		int currentType = this->noteType[latestNoteHit];

		// note type = 1; up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && inputFrames == 0)
		{
			if (currentType == 1 &&
				currentNote->getPosition().x > MIN_THRESHOLD &&
				currentNote->getPosition().x <= MAX_THRESHOLD)
			{
				score++;
				result = "HIT";
				currentNote->setAnimation(NoteObject::pop);
			} else
			{
				result = "MISS";
				currentNote->setAnimation(NoteObject::red);
			}
			latestNoteHit++;
			//currentNote->setActive(false);

			inputFrames++;
		}

		// note type = -1; down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && inputFrames == 0)
		{
			if (currentType == -1 &&
				currentNote->getPosition().x > MIN_THRESHOLD &&
				currentNote->getPosition().x <= MAX_THRESHOLD)
			{
				score++;
				result = "HIT";
				currentNote->setAnimation(NoteObject::pop);
			}
			else
			{
				result = "MISS";
				currentNote->setAnimation(NoteObject::red);
			}
			latestNoteHit++;
			//currentNote->setActive(false);

			inputFrames++;
		}

		// first in note
		sf::Keyboard::Key key = sf::Keyboard::Key::Up;
		if (this->noteType[latestNoteHit] < 0)
			key = sf::Keyboard::Key::Down;
	}

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
