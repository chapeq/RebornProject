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
	void Stop();

private :
	sf::Music backgroundMusic;
	sf::SoundBuffer collect;
	sf::SoundBuffer smallgameover;
	sf::SoundBuffer GameOver;
	sf::Sound sound1, sound2, sound3;
};

