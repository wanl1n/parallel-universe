#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	this->active = false;
}

void TextureDisplay::initialize()
{
	std::cout << "Texture Display initializing" << std::endl;
	while (this->numDisplayed < maxAssetCount)
	{
		TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
		this->numDisplayed++;
	}

	while (this->iconList.size() < maxAssetCount)
	{
		this->loadingAssets = true;
	}
	this->loadingAssets = false;
	std::cout << "Texture Display initialized" << std::endl;
}

void TextureDisplay::processInput(sf::Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	for (IconObject* icon : this->iconList)
	{
		icon->setActive(active);
	}
}

void TextureDisplay::onFinishedExecution()
{
	this->spawnObject();
}

void TextureDisplay::spawnObject()
{
	this->guard.lock();

	String objectName = "Cat_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);
	
	//std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
	iconObj->setActive(false);

	this->guard.unlock();
}
