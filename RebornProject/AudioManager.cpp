#include "stdafx.h"
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
		
	if (!collect.loadFromFile("Assets/collectsound.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	if (!smallgameover.loadFromFile("Assets/smallgameover.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	if (!GameOver.loadFromFile("Assets/GameOver.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;
		
}

AudioManager::~AudioManager()
{
}

void AudioManager::PlayMusic()
{
	if (!backgroundMusic.openFromFile("Assets/backgroundMusic.ogg"))
		std::cout << "ERROR Failed to load music" << std::endl;

	//backgroundMusic.play();
	backgroundMusic.setLoop(true);
}

void AudioManager::PlayCollect()
{
	sf::Sound sound;
	sound.setBuffer(collect);
	sound.play();
}

void AudioManager::PlayHit()
{
	sf::Sound sound;
	sound.setBuffer(smallgameover);
	sound.play();
}

void AudioManager::PlayGameOver()
{
	sf::Sound sound;
	sound.setBuffer(GameOver);
	sound.play();
}