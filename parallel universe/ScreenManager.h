#pragma once
#include <unordered_map>

#include "Screen.h"
#include "GameScreen.h"
#include "LoadingScreen.h"

class ScreenManager
{
public:
	typedef std::unordered_map<Screen::ScreenName, Screen*> ScreenMap;
	static ScreenManager* getInstance();
	void initialize();

	void loadScreen(Screen::ScreenName screenName);

private:
	ScreenManager();
	ScreenManager(ScreenManager const&) {};             // copy constructor is private
	ScreenManager& operator=(ScreenManager const&) {};  // assignment operator is private
	static ScreenManager* sharedInstance;

	bool loading = false;
	Screen* currentScreen;
	ScreenMap screenMap;
};
