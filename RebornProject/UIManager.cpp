#include "stdafx.h"
#include "UIManager.h"
#include <iostream>


UIManager::UIManager()
{
	if (!fontStart.loadFromFile("Assets/retro.ttf"))
		std::cout << "ERROR Failed to load font" << std::endl;

	startText.setFont(this->fontStart);
	startText.setCharacterSize(80);
	startText.setFillColor(sf::Color::White);
	startText.setPosition(100, 200);
	startText.setString("Press Space To Start !");

	if (!fontScore.loadFromFile("Assets/rainyhearts.ttf"))
		std::cout << "ERROR Failed to load font" << std::endl;

	scoreText.setFont(fontScore);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(0, 0);
	scoreText.setString("Score : 0");
}

UIManager::~UIManager()
{
}

void UIManager::AfficheScore(std::string score)
{
	scoreText.setString(score);
}

void UIManager::AfficheRebornText()
{
	rebornText.setFont(fontStart);
	rebornText.setString("You Died ! Press R To Reborn !");
	rebornText.setPosition(70, 200);
	rebornText.setCharacterSize(70);
	rebornText.setFillColor(sf::Color::White);
}

void UIManager::AfficheGameOverText()
{
	if (!fontGameOver.loadFromFile("Assets/game_over.ttf"))
		std::cout << "ERROR Failed to load font" << std::endl;

	gameOverText.setFont(fontGameOver);
	gameOverText.setString("GAME OVER !");
	gameOverText.setPosition(120, 60);
	gameOverText.setCharacterSize(230);
	gameOverText.setFillColor(sf::Color::White);

	scoreText.setPosition(300, 300);
}

void UIManager::HideStartText()
{
	startText.setCharacterSize(0);
	startText.setFillColor(sf::Color::Black);
}

void UIManager::HideRebornText()
{
	rebornText.setCharacterSize(0);
	rebornText.setFillColor(sf::Color::Black);
}

void UIManager::Draw(sf::RenderTarget& target)
{
	target.draw(startText);
	target.draw(scoreText);
	target.draw(rebornText);
	target.draw(gameOverText);
}