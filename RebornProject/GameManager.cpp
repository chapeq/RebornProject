#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}


void GameManager::GameStarting()
{
	m_Audio.PlayMusic();
	m_UIManage.HideStartText();
}


void GameManager::Scoring(std::string scoreText)
{
	m_UIManage.ShowScore(scoreText);
	m_Audio.PlayCollect();
}

void GameManager::Losing()
{
	m_Audio.PlayHit();
	m_UIManage.ShowRebornText();
}

void GameManager::Restarting()
{
	m_Audio.PlayMusic();
	m_UIManage.HideRebornText();
}

void GameManager::GameOver()
{
	m_Audio.PlayGameOver();
	m_UIManage.ShowGameOverText();
}

void GameManager::DrawUI(sf::RenderTarget& target)
{
	m_UIManage.Draw(target);
}