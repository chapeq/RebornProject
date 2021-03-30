#pragma once
#include "UIManager.h"
#include "TimeManager.h"
#include "AudioManager.h"

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
    GameState m_State; 
    UIManager m_UIManage;
    AudioManager m_Audio;
    TimeManager* m_Timer;
    sf::Vector2f m_windowSize;
    virtual void Update() = 0;
    virtual void Render(sf::RenderTarget& target) = 0;
    virtual void RenderDebugMenu(sf::RenderTarget& target) = 0;

private:
    sf::RenderWindow m_window;
};

