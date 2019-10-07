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
	// Двумерный массив с объектами карты
	sf::Texture BackgrTex;
	sf::Sprite Backgr;
	self::FLayer* Layers = new self::FLayer;
	// * Информация о карте 

public:
	// Инициализация уровня. Чтение мира из файлов и занос его в массив.
	void CreateWorld(sf::Uint32 LvlName);

	// Функция отрисовки
	void DrawWorld(sf::RenderWindow& window);

	// Функция движения мира по позиции пешки.
	void MoveWorld();
	
	//
	sf::Vector2f getStartPos();

	
};

