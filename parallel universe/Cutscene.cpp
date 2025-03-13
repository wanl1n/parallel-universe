#include "Cutscene.h"

#include "TextureManager.h"

Cutscene::Cutscene(std::string name)
    : AGameObject(name)
{
}

void Cutscene::initialize()
{
    TextureManager::getInstance()->loadStreamingAssets(this);
}

void Cutscene::update(sf::Time deltaTime)
{
    if (!loading)
    {
        this->ticks += deltaTime.asSeconds();
        if (this->ticks > 1.0f / this->fps)
        {
            this->ticks = 0;
            this->incrementFrame();
        }
    }
}

void Cutscene::incrementFrame() {
    index++;
    if (index >= totalFrames) index = totalFrames-1;
    this->setCurrentFrame(index);
}

void Cutscene::setTexture(sf::Texture* texture)
{
    this->sprite = new sf::Sprite(*texture);
    this->sprite->setTexture(*texture);
}

void Cutscene::setCurrentFrame(int nCurrentFrame) {
    sf::Texture* frame = TextureManager::getInstance()->getStreamTextureFromList(nCurrentFrame);
    
    this->setTexture(frame);
}

void Cutscene::onFinishedExecution()
{
    loading = false;
    //this->framesLoaded++;
    //std::cout << "cutscene loaded" << std::endl;
}
