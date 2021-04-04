#include "stdafx.h"
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
	if (!bufCollect.loadFromFile("Assets/collectsound.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	if (!bufSmallgameover.loadFromFile("Assets/smallgameover.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	if (!bufGameOver.loadFromFile("Assets/GameOver.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	if (!backgroundMusic.openFromFile("Assets/backgroundMusic.ogg"))
		std::cout << "ERROR Failed to load music" << std::endl;

	sdCollect.setBuffer(bufCollect);
	sdSmallgameover.setBuffer(bufSmallgameover);
	sdGameOver.setBuffer(bufGameOver);
}

AudioManager::~AudioManager()
{
}

void AudioManager::PlayMusic()
{
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
}

void AudioManager::PlayCollect()
{
	if (sdCollect.getStatus() != sf::Sound::Status::Playing)
		sdCollect.play();
}

void AudioManager::PlayHit()
{
	backgroundMusic.pause();
	sdSmallgameover.play();
}

void AudioManager::PlayGameOver()
{
	backgroundMusic.pause();
	sdGameOver.play();
}