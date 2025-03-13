#pragma once
//#include "IETThread.h"
#include "IWorkerAction.h"
#include "../Screen.h"
#include "../GameScreen.h"

class IExecutionEvent;

// Converted to IWorkerAction, now it's a Job.
class SceneLoader : public IWorkerAction
{
public:
	SceneLoader(Screen::ScreenName name, Screen* screen);
	~SceneLoader();

private:
	void onStartTask() override;

	Screen::ScreenName name;
	IExecutionEvent* execEvent;
	Screen* screen;
};