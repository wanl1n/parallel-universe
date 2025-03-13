#pragma once
#include "Screen.h"
#include "TextureDisplay.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen();
	void initializeDisplay() override;

	void processInput() override;
	void onFinishedExecution() override;

private:
	TextureDisplay* display;
};

