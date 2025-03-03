#include "SceneLoader.h"
#include <iostream>
#include <random>

#include "IETThread.h"
#include "../TextureManager.h"
#include "../StringUtils.h"
#include "IExecutionEvent.h"
#include "../ScreenManager.h"

SceneLoader::SceneLoader(Screen::ScreenName name, GameScreen* screen)
{
	this->screen = screen;
	this->execEvent = screen;
	this->name = name;
}

SceneLoader::~SceneLoader()
{
	//std::cout << "Destroying scene loader. " << std::endl;
}

void SceneLoader::onStartTask()
{
	//std::cout << "Running scene loader " << std::endl;
	switch (name)
	{
	case Screen::ScreenName::game:
		this->screen->initializeDisplay();
		break;
	default:
		break;
	}

	this->execEvent->onFinishedExecution();

	//delete after being done
	delete this;
}