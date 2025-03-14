#pragma once
#include "LoadingText.h"
#include "Pot.h"
#include "Screen.h"
#include "SpriteObject.h"

class LoadingScreen : public Screen
{
public:
	LoadingScreen(int* score);
	~LoadingScreen();

	void initializeDisplay() override;

	void loadZenGarden();

	void update(float deltaTime) override;
	void onFinishedExecution() override;

	void transition();

private:
	std::vector<AGameObject*> objects;

	LoadingText* message;
	float ticks = 0;
	int inputFrames = 0;

	// zen garden
	SpriteObject* wateringCan;
	std::vector<Pot*> pots;

	bool screamed = false;
	bool transitioning = false;
	bool pulled = false;
	bool ready = false;
	SpriteObject* bungee;
	float bungeeSpeed = 300;
};