#pragma once
#include <string>
#include <vector>

#include "AnimatedObject.h"
#include "Threading/IExecutionEvent.h"

class Screen : public IExecutionEvent
{
public:
	typedef std::vector<std::string> ObjectList;
	enum ScreenName { main, loading, game};

	Screen(ScreenName name);
	~Screen();

	virtual void update(float deltaTime);
	virtual void processInput();
	virtual void loadScreen();
	virtual void unloadScreen();
	void onFinishedExecution() override;

	ScreenName getName() { return name; }
	bool isLoading() { return load; }

protected:
	ScreenName name;
	ObjectList objectList;
	bool load = true;
};
