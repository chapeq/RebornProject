#pragma once
#include "UIManager.h"
#include "AudioManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void GameStarting();
	void Scoring(std::string scoreText);
	void Losing();
	void Restarting();
	void GameOver();
	void DrawUI(sf::RenderTarget& target);

private:
	UIManager m_UIManage;
	AudioManager m_Audio;
};

