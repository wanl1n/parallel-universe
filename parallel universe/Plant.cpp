#include "Plant.h"


#include "GameObjectManager.h"
#include "MathUtils.h"
#include "SpriteObject.h"
#include "TextureManager.h"

Plant::Plant(std::string name, std::string objName, Pot* pot)
    : AGameObject(name)
{
    this->pot = pot;
    this->animNames[idle] = "idle";

    this->animFramesCount[idle] = 3;

    this->currentAnim = idle;
    this->objName = objName;
    this->blinkInterval = MathUtils::randomInt(3, 6);

    this->initialize();
}

void Plant::initialize()
{
    TextureManager::getInstance()->loadSpriteSheets(objName, animNames[idle]);

    //assign texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(objName + " " + animNames[idle], 0);
    this->setTexture(texture);

    /*needWater = new SpriteObject(name + "need water", "need water");
    GameObjectManager::getInstance()->addObject(needWater);
    needWater->setActive(false);
    needWater->setPosition(posX + 20, posY + 20);*/
}

void Plant::processInput(sf::Event event)
{
}

void Plant::bounce(float deltaTime)
{
    float targetX = initPos.x + xOffset;
    float targetY = initPos.y + yOffset;

    if (!this->movingRight)
        targetX = initPos.x - xOffset;
    else
        targetX = initPos.x + xOffset;

    if (posX >= initPos.x + xOffset && movingRight)
        this->movingRight = false;
    else if (posX <= initPos.x - xOffset && !movingRight)
        this->movingRight = true;

    if (!this->movingUp)
        targetY = initPos.y - yOffset;
    else
        targetY = initPos.y + yOffset;

    if (posY >= initPos.y + yOffset && movingUp)
        this->movingUp = false;
    else if (posY <= initPos.y - yOffset && !movingUp)
        this->movingUp = true;

    float newX = MathUtils::interpolateTowards(posX, targetX, 10 * deltaTime);
    float newY = MathUtils::interpolateTowards(posY, targetY, 10 * deltaTime);
    //std::cout << targetX << ", " << targetY << std::endl;
	this->setPosition(newX, newY);
}

void Plant::update(sf::Time deltaTime)
{
    blink(deltaTime.asSeconds());
    bounce(deltaTime.asSeconds());

    /*if (pot->isDry())
    {
        needWater->setActive(true);
    } else
    {
        needWater->setActive(false);
    }*/

    this->blinkTimer += deltaTime.asSeconds();
    if (this->blinkTimer > this->blinkInterval)
    {
        this->blinkTimer = 0;
        this->blinking = true;
    }
    //needWater->setPosition(posX+sprite->getTexture().getSize().x, posY+sprite->getTexture().getSize().y/2);
}

void Plant::incrementFrame() {
    if (this->frameIndex == 0)
    {
        if (openingEyes)
        {
	        blinking = false;
            openingEyes = false;
        }
        else
            frameIndex++;
    }
    else if (this->frameIndex == 1)
    {
        if (openingEyes)
            frameIndex--;
        else
            frameIndex++;
    }
    else if (this->frameIndex == 2) {
        frameIndex--;
        openingEyes = true;
    } 

    this->setCurrentFrame(frameIndex);
}

void Plant::setTexture(sf::Texture* texture)
{
    float textureWidth = texture->getSize().x;
    float textureHeight = texture->getSize().y;
    float scaleX = textureWidth / 168.0f;
    float scaleY = textureHeight / 168.0f;

    this->sprite = new sf::Sprite(*texture);
    this->sprite->setTexture(*texture);
    this->sprite->setScale(sf::Vector2f(scaleX, scaleY));
}

void Plant::setCurrentFrame(int nCurrentFrame) {
    sf::Texture* frame = TextureManager::getInstance()->getFromTextureMap(this->objName + " " + this->animNames[currentAnim], nCurrentFrame);
    this->setTexture(frame);
}

void Plant::setAnimation(AnimName animName)
{
    this->currentAnim = animName;
}

void Plant::blink(float deltaTime)
{
	if (blinking) {
		this->ticks += deltaTime;
		if (this->ticks > 0.1f / this->fps)
		{
			this->ticks = 0;
			this->incrementFrame();
		}
	}
}

void Plant::setInitPos(float x, float y)
{
    this->initPos = sf::Vector2f(x, y);

    float randX = MathUtils::randomFloat(x - xOffset, x + xOffset);
    float randY = MathUtils::randomFloat(y - yOffset, y + yOffset);
    this->setPosition(randX, randY);
}