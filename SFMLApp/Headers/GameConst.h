#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const std::string SpritePath = "..\\Resource\\Sprites\\";
const std::string LevelPath = "..\\Resource\\Levels\\";
const std::string FontPath = "..\\Resource\\";
const std::string MenuFont = "MenuFont.ttf";
const float g = 0.004; // � �������� � ���. ���� 32px = 1m

enum EEndStatus
{
	Menu,
	Exit,
	StartGame,		
	ReturnGame,
	FileLoadFaled,
	GameError,
	Nothing,
};

enum EDirection {
	left,
	right,
	top,
	down,
	nowhere
};