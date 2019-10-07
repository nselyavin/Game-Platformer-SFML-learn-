#pragma once

const std::string SpritePath = "..\\Resource\\Sprites\\";
const std::string LevelPath = "..\\Resource\\Levels\\";
const std::string FontPath = "..\\Resource\\";

enum EEndStatus
{
	Menu,
	Exit,
	StartGame,		
	ReturnGame,
	FileLoadFaled,
	GameError,
};
