#pragma once
#include "Cutscene.h"
#include "Screen.h"

class GameScreen : public Screen
{
public:
	GameScreen(int* score);
	~GameScreen();
	void initializeDisplay() override;

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

