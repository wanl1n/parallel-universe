#pragma once
#include <unordered_map>

#include "Screen.h"
#include "GameScreen.h"
#include "LoadingScreen.h"
#include "Threading/ThreadPool.h"

class ScreenManager
{
public:
	typedef std::unordered_map<Screen::ScreenName, Screen*> ScreenMap;
	static ScreenManager* getInstance();
	void initialize();

	void addScreen(Screen::ScreenName screenName, Screen* screen);
	void loadScreen(Screen::ScreenName screenName);
	void processInput();
	void update(float deltaTime);

	bool loadingProgress();

private:
	ScreenManager();
	ScreenManager(ScreenManager const&) {};             // copy constructor is private
	ScreenManager& operator=(ScreenManager const&) {};  // assignment operator is private
	static ScreenManager* sharedInstance;

	Screen* currentScreen;
	ScreenMap screenMap;
	ThreadPool* threadPool;
};
