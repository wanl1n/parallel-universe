#include "SceneLoader.h"

#include "IExecutionEvent.h"
#include "../ScreenManager.h"

SceneLoader::SceneLoader(Screen::ScreenName name, Screen* screen)
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
	this->screen->initializeDisplay();
	this->execEvent->onFinishedExecution();

	//delete after being done
	delete this;
}