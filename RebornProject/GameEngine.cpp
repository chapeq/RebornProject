#include "stdafx.h"
#include "GameEngine.h"
#include <iostream>


static const int MAX_FRAMERATE{ 60 };
static const sf::Vector2f WINDOW_SIZE{ 800, 600 };
static const char* APP_NAME = "REBORN";

GameEngine::GameEngine()
{
	m_window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), APP_NAME, sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(MAX_FRAMERATE);

	auto image = sf::Image{};
	if (!image.loadFromFile("Assets/rebornlogo.png"))
		std::cout << "ERROR Failed to load font" << std::endl;

	m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	m_windowSize = WINDOW_SIZE;
	m_State = GameState::Start;

	ImGui::SFML::Init(m_window);

	float deltaTime{ 1.0f / MAX_FRAMERATE };
	sf::Clock clock;
	m_Timer = new TimeManager(clock, deltaTime);
}

GameEngine::~GameEngine()
{
	delete m_Timer;
	ImGui::SFML::Shutdown();
}

void GameEngine::RunGameLoop()
{
	bool toggleImGui = true;

	while (m_window.isOpen())
	{
		m_Timer->RestartClock();

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
				else if ((event.key.code == sf::Keyboard::Space) && (m_State == GameState::Start))
				{
					m_State = GameState::Playing;
					m_manager.GameStarting();
				}
				else if ((event.key.code == sf::Keyboard::R) && (m_State == GameState::Lose))
				{
					m_State = GameState::Playing;
					m_manager.Restarting();
				}
				break;
			case sf::Event::Resized:
			{
				break;
			}
			}

			ImGui::SFML::ProcessEvent(event);
		}

		ImGui::SFML::Update(m_window, m_Timer->RestartClock());

		Update();
		Render(m_window);
		RenderDebugMenu(m_window);

		ImGui::EndFrame();
		if (toggleImGui)
		{
			ImGui::SFML::Render(m_window);
		}

		m_window.display();

		m_Timer->SetDeltaTime();
	}
}