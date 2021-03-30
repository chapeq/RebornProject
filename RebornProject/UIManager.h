#pragma once
class UIManager
{
public:
	UIManager();
	~UIManager();

	void AfficheScore(std::string scoreText);
	void AfficheRebornText();
	void AfficheGameOverText();
	void HideStartText();
	void HideRebornText();
	void Draw(sf::RenderTarget& target);

private :
	sf::Font fontStart;
	sf::Font fontScore;
	sf::Font fontGameOver;
	sf::Text scoreText;
	sf::Text startText;
	sf::Text rebornText;
	sf::Text gameOverText;
};

