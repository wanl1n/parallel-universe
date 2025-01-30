#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::initialize()
{
	
}

void TextureDisplay::processInput(sf::Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	//this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
	this->ticks += deltaTime.asMilliseconds();
	
	//<code here for spawning icon object periodically>
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->startedStreaming = true;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY && this->numDisplayed < 480)
	{
		std::cout << "[Texture Display]: SINGLE_STREAM Spawning object" << std::endl;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed);
		this->numDisplayed++;
		this->spawnObject();
	}
}

//void TextureDisplay::onFinishedExecution()
//{
//	this->spawnObject(); //executes spawn once the texture is ready.
//}

void TextureDisplay::spawnObject()
{
	//this->guard.lock();

	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);

	//this->guard.unlock();
}
