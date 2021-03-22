#pragma once
#include "UIManager.h"
#include "TimeManager.h"

enum class GameState
{
    Start,
    Playing,
    Lose,
    End,
};

class GameEngine
{
public :
    GameEngine();
    virtual ~GameEngine();
    void RunGameLoop();
  

protected:
    GameState mState; 
    UIManager uiManage;
    TimeManager* timer;
    sf::Vector2f windowSize;
    virtual void Update() = 0;
    virtual void Render(sf::RenderTarget& target) = 0;
    virtual void RenderDebugMenu(sf::RenderTarget& target) = 0;

private:
    sf::RenderWindow m_window;
};

