#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;

	static BaseRunner* getInstance();
	static BaseRunner* sharedInstance;
	float getFPS() const;

	BaseRunner(const BaseRunner&) = delete;
	BaseRunner(BaseRunner&&) = delete;
	BaseRunner& operator=(const BaseRunner&) = delete;
	BaseRunner& operator=(BaseRunner&&) = delete;

	BaseRunner();
	void run();

private:
	
	sf::RenderWindow window;
	float fps = 0.0f;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};