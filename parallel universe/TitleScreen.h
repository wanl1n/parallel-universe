#pragma once
#include "Screen.h"

class TitleScreen : public Screen
{
public:
	TitleScreen();
	~TitleScreen();
	void initializeDisplay() override { Screen::initializeDisplay(); }

	void update(float deltaTime) override;
	void processInput() override;
};

