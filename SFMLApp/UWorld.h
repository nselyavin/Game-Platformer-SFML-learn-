/*
	Класс для содержания и отрисовки мира уровня (все что не игрок).
	Здесь происходит сдвиг камеры игры, при движении игрока.
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include "GameConst.h"
#include "XMLtoMap.h"

namespace self {
	struct FLayer
	{
		std::vector <std::vector<sf::Sprite>> Blocks;
	};
}

#pragma once
class UWorld
{
private:
	// Размеры карты
	sf::Vector2i LvlSize;
	// Размер одного тайла
	sf::Vector2i TileSize;
	// Размер тайл сета
	sf::Vector2i TileSetSize;
	// Объекты заднего фона карты
	sf::Texture BackgrTex;
	sf::Sprite Backgr;
	// Объект тайлсета
	sf::Texture TileSetTex;
	// Стартовая позиция игрока
	sf::Vector2f StartPos;
	// Количевство слоев
	int AmountLayers = 0;
	// Массив слоев
	self::FLayer* Layers = new self::FLayer;
	// Массив коллизии. ToDo массив коллизии убрать если не поадоиться 
	std::vector <std::vector <bool>> CollsMap;
	// * Информация о карте 

public:
	
	~UWorld();

	// Инициализация уровня. Чтение мира из файлов и занос его в массив.
	void CreateWorld(sf::Uint32 LvlName);

	// Функция отрисовки
	void DrawWorld(sf::RenderWindow& window);

	// Возвращает стартовую позицию игрока
	sf::Vector2f getStartPos();

	
};

