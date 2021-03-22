#include "stdafx.h"
#include "GameEngine.h"


static const float MAX_FRAMERATE{ 60.0f };
static const sf::Vector2f WINDOW_SIZE{ 800, 600 };
static const char* APP_NAME = "REBORN" ;

GameEngine::GameEngine()
{
    m_window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), APP_NAME, sf::Style::Titlebar | sf::Style::Close);
    m_window.setFramerateLimit(MAX_FRAMERATE);

    windowSize = WINDOW_SIZE;
    mState = GameState::Start;

    ImGui::SFML::Init(m_window);

    float deltaTime{ 1.0f / MAX_FRAMERATE };
    sf::Clock clock;
    timer = new TimeManager(clock, deltaTime);
}

GameEngine::~GameEngine()
{
    ImGui::SFML::Shutdown();
}

void GameEngine::RunGameLoop()
{

        bool toggleImGui = true;

        while (m_window.isOpen())
        {
            timer->restartClock();

            sf::Event event;
            while (m_window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        m_window.close();
                    else if ((event.key.code == sf::Keyboard::Space) && (mState == GameState::Start))
                    {
                        mState = GameState::Playing;
                        uiManage.hideStartText();
                    }
                    else if ((event.key.code == sf::Keyboard::R) && (mState == GameState::Lose))
                    {
                        mState = GameState::Playing;
                        uiManage.hideRebornText();
                    }
                    break;
                case sf::Event::Resized:
                {
                    break;
                }
                }

                ImGui::SFML::ProcessEvent(event);
            }

            ImGui::SFML::Update(m_window, timer->restartClock());

            Update();
            Render(m_window);
            RenderDebugMenu(m_window);

            ImGui::EndFrame();
            if (toggleImGui)
            {
                ImGui::SFML::Render(m_window);
            }

            m_window.display();

            timer->setDeltaTime();
        }
    }