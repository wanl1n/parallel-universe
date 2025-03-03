#pragma once
#include "NoteObject.h"
#include "Screen.h"

class LoadingScreen : public Screen
{
public:
	typedef std::vector<NoteObject*> NotesList;

	LoadingScreen();
	~LoadingScreen();

	void update(float deltaTime) override;
	void processInput() override;

private:
	const float MIN_THRESHOLD = 1200.0f;
	const float MAX_THRESHOLD = 1600.0f;

	AnimatedObject* catPiano;
	NotesList notes;
	float timeStamps[10] = { 3.912f, 6.648f, 9.384f,
							13.776f, 17.856f, 19.272f,
							21.192f, 22.560f, 24.744f,
							26.088f, };
	float noteType[10] = { -1, -1, 1, 1, -1, -1, 1, -1, 1, -1 };
	float timeOffset = 1.0f;
	int notesCount = 10;
	int nextNoteIndex = 0;
	int latestNoteHit = 0;
	float ticks = 0;
	int score = 0;
};

