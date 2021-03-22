#pragma once
class UIManager
{
public:
	UIManager();
	~UIManager();

	void afficheScore(std::string scoreText);
	void afficheRebornText();
	void afficheGameOverText();
	void hideStartText();
	void hideRebornText();
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

