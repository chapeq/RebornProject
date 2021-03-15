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
    mState = Start;

    ImGui::SFML::Init(m_window);
}

GameEngine::~GameEngine()
{
    ImGui::SFML::Shutdown();
}

void GameEngine::RunGameLoop()
{
        float deltaTime{ 1.0f / MAX_FRAMERATE };
        sf::Clock clock;

        bool toggleImGui = true;

        while (m_window.isOpen())
        {
            clock.restart();

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
                    else if ((event.key.code == sf::Keyboard::Space) && (mState == Start))
                    {
                        mState = Playing;
                        //startText.setCharacterSize(0);
                        //startText.setFillColor(sf::Color::Black);
                    }
                    else if ((event.key.code == sf::Keyboard::R) && (mState == Lose))
                    {
                        mState = Playing;
                        // startText.setCharacterSize(0);
                         //startText.setFillColor(sf::Color::Black);
                    }
                    break;
                case sf::Event::Resized:
                {
                    break;
                }
                }

                ImGui::SFML::ProcessEvent(event);
            }

            ImGui::SFML::Update(m_window, clock.restart());

            Update(deltaTime);
            Render(m_window);
            RenderDebugMenu(m_window);

            ImGui::EndFrame();
            if (toggleImGui)
            {
                ImGui::SFML::Render(m_window);
            }

            m_window.display();

            deltaTime = clock.getElapsedTime().asSeconds();
        }
    }