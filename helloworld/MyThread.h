#pragma once

#include "IETThread.h"

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
class MyThread : public IETThread
{
public:
	MyThread(int id = 0);
	virtual ~MyThread();

public:
	void run() override;
	void dismiss();

private:
	int id;
	bool running;
};

