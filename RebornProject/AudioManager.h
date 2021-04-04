#pragma once
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlayMusic();
	void PlayCollect();
	void PlayHit();
	void PlayGameOver();

private:
	sf::Music backgroundMusic;
	sf::SoundBuffer bufCollect;
	sf::SoundBuffer bufSmallgameover;
	sf::SoundBuffer bufGameOver;
	sf::Sound sdCollect;
	sf::Sound sdSmallgameover;
	sf::Sound sdGameOver;
};

