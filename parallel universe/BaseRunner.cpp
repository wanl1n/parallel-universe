#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HO: Entity Component", sf::Style::Close, sf::State::Fullscreen) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();
	/*for (int i = 0; i < 480; i++)
		TextureManager::getInstance()->loadSingleStreamAsset(i);*/

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock CClock = sf::Clock();
	sf::Time tTimeSinceLastUpdate = sf::Time::Zero;

	while (this->window.isOpen()) {
		tTimeSinceLastUpdate += CClock.restart();

		while (tTimeSinceLastUpdate > TIME_PER_FRAME) {
			this->processEvents();
			this->update(tTimeSinceLastUpdate);
			tTimeSinceLastUpdate -= TIME_PER_FRAME;
		}

		this->render();
	}
}

void BaseRunner::processEvents()
{
	if (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
		{
			this->window.close();
		}
		else {
			GameObjectManager::getInstance()->processInput(event.value());
		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS() const
{
	return this->fps;
}