#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "ScreenManager.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Meowrapy", sf::Style::Close) {

	ShowWindow(window.getNativeHandle(), SW_SHOWMAXIMIZED);

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	//load initial textures: BG
	TextureManager::getInstance()->loadFromAssetList();

	this->initializeObjects();

	ScreenManager::getInstance()->initialize();
} 

void BaseRunner::initializeObjects()
{
	//load objects
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	while (this->window.isOpen()) {

		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;
	}
}

void BaseRunner::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->window.close();
	}

	if (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
		{
			this->window.close();
		}
		else {
			GameObjectManager::getInstance()->processInput(event.value());
		}
	}
	ScreenManager::getInstance()->processInput();
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
	ScreenManager::getInstance()->update(elapsedTime.asSeconds());
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