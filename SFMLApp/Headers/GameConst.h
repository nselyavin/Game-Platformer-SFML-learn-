#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const std::string SpritePath = "..\\Resource\\Sprites\\";
const std::string LevelPath = "..\\Resource\\Levels\\";
const std::string FontPath = "..\\Resource\\";
const std::string MenuFont = "MenuFont.ttf";
const float g = 0.02; // В пикселях в тик. Если 32px = 1m

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

// ToDo поменят значения, влево всегда -1, вправо 1
enum EDirection {
	Left = +1,
	Right = -1,
	Top = +1,
	Down = -1,
	Nowhere = 0
};
