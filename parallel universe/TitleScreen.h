#pragma once
#include "Screen.h"

class TitleScreen : public Screen
{
public:
	TitleScreen(int* score);
	~TitleScreen();
	void initializeDisplay() override { Screen::initializeDisplay(); }

	void update(float deltaTime) override;
	void processInput() override;
};

