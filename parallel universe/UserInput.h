#pragma once
#include <SFML/Window/Event.hpp>

class UserInput
{
public:
    UserInput();
    void perform();
    void resetLeftClick();
    void assignEvent(sf::Event eEvent);

    bool isLeftClick();
    bool isRightClick();
    sf::Vector2f getLocation();

private:
    bool bLeftClick;
    bool bRightClick;
    sf::Vector2f vecLocation;

    void processKeyInput(sf::Keyboard::Key key, bool bPressed);
    void processMouseInput(sf::Mouse::Button inMouse, bool bPressed);
};