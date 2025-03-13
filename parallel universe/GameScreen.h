#pragma once
#include <iostream>

#include "Cutscene.h"
#include "Screen.h"
#include "TextureDisplay.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen();
	void initializeDisplay() override;

	void loadScreen() override;

	void update(float deltaTime) override;
	void processInput() override;
	void onFinishedExecution() override;
	bool loadingProgress()
	{
		//if (this->cs != nullptr)std::cout << "Game screen loading progress " << this->cs->loadingProgress() << std::endl;
		if (this->cs != nullptr) return this->cs->isLoading();
		else return true;
	}

private:
	//TextureDisplay* display;
	Cutscene* cs;
};

