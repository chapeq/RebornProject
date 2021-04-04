#include "stdafx.h"
#include "Config.h"
#include <iostream>
#include <fstream>



void GetInitConfig(Parameters& out)
{
	std::ifstream file("Assets/Config.txt");
	std::string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace),
				line.end());
			if (line[0] == '#' || line.empty())
				continue;


			std::size_t delimiterPos = line.find("=");
			std::string param = line.substr(0, delimiterPos);

			if (param == "Increasedifficulty")
			{
				if (line.substr(delimiterPos + 1) == "true")
					out.increaseDifficulty = true;
				else if (line.substr(delimiterPos + 1) == "false")
					out.increaseDifficulty = false;
			}
			if (param == "Collectiblespeed")
				out.collectibleSpeed = std::stof(line.substr(delimiterPos + 1));
			if (param == "Obstaclespeed")
				out.obstacleSpeed = std::stof(line.substr(delimiterPos + 1));
			if (param == "CollectibleSpawnTime")
				out.collectibleSpawnTime = std::stof(line.substr(delimiterPos + 1));
			if (param == "ObstacleSpawnTime")
				out.obstacleSpawnTime = std::stof(line.substr(delimiterPos + 1));
			if (param == "NombreMaxCollectible")
				out.nbrMaxCollectible = std::stoi(line.substr(delimiterPos + 1));
			if (param == "NombreMaxObstacle")
				out.nbrMaxObstacle = std::stoi(line.substr(delimiterPos + 1));
			if (param == "Playerspeed")
				out.playerSpeed = std::stof(line.substr(delimiterPos + 1));
			if (param == "Playersize")
				out.playerRadius = std::stof(line.substr(delimiterPos + 1));
		}
	}
	else
	{
		std::cout << "Couldn't open config file for reading.\n";
	}
}
