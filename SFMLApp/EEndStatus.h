#pragma once

#define SritePath "..\\Resource\Sprites\"
#define LevelPath "..\\Resource\Levels\"
#define FontPath "..\\Resource\"

enum EEndStatus
{
	Menu,
	Exit,
	StartGame,		// Или выбор уровня
	FileLoadFaled,
	GameError,
};
