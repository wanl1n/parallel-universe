#pragma once
#include "AGameObject.h"
#include "Threading/IExecutionEvent.h"

class Cutscene : public AGameObject, public IExecutionEvent
{
public:
    Cutscene(String name);
    void initialize();
    void processInput(sf::Event event) {}
    void update(sf::Time deltaTime);

    void incrementFrame();
    void setTexture(sf::Texture* texture);
    void setCurrentFrame(int nCurrentFrame);

    void onFinishedExecution() override;
    bool isLoading() const { return this->loading; }

protected:
    int fps = 20;
    int totalFrames = 800;
    float ticks = 0;
    int index = 0;
    bool loading = true;
};

