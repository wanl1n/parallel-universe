#pragma once
#include "NoteObject.h"
#include "SpriteObject.h"

class Comeowser : public SpriteObject
{
public:
	Comeowser();
	~Comeowser();

	void initialize() override;
};