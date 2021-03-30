#include "stdafx.h"
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
			
}

AudioManager::~AudioManager()
{
}

void AudioManager::PlayMusic()
{
	if (!backgroundMusic.openFromFile("Assets/backgroundMusic.ogg"))
		std::cout << "ERROR Failed to load music" << std::endl;

	backgroundMusic.play();
	backgroundMusic.setLoop(true);
}

void AudioManager::PlayCollect()
{
	if (!collect.loadFromFile("Assets/collectsound.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	sound1.setBuffer(collect);
	sound1.play();
}

void AudioManager::PlayHit()
{
	if (!smallgameover.loadFromFile("Assets/smallgameover.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	sound2.setBuffer(smallgameover);
	sound2.play();
}

void AudioManager::PlayGameOver()
{
	if (!GameOver.loadFromFile("Assets/GameOver.ogg"))
		std::cout << "ERROR Failed to load sound" << std::endl;

	sound3.setBuffer(GameOver);
	sound3.play();
}