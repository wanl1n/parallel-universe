#pragma once
#include "Screen.h"

class LoadingScreen : public Screen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void processInput() override;

private:
	AnimatedObject* catPiano;
};

