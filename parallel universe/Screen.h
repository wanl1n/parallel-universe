#pragma once
#include <string>
#include <vector>

class Screen
{
public:
	typedef std::vector<std::string> ObjectList;
	enum ScreenName { main, loading, game};

	Screen(ScreenName name);
	~Screen();

	virtual void loadScreen();
	virtual void unloadScreen();
	ScreenName getName() { return name; }

protected:
	ScreenName name;
	ObjectList objectList;
};
