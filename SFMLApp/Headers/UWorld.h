/*
	Класс для содержания и отрисовки мира уровня (все что не игрок).
	Здесь происходит сдвиг камеры игры, при движении игрока.
*/
#pragma once

#include <vector>
#include <string>
#include <thread>
#include "GameConst.h"
#include "XMLtoMap.h"
#include <Windows.h>


namespace world {
	struct FLayer
	{
		std::vector <std::vector<sf::Sprite>> Blocks;
	};
}

class UWorld
{
private:
	CRITICAL_SECTION m_lockHorizontal;
	CRITICAL_SECTION m_lockVertical;
	// Размеры карты
	sf::Vector2i LvlSize;
	// Размер одного тайла
	sf::Vector2i TileSize;
	// Размер тайл сета
	sf::Vector2i TileSetSize;
	// Карта коллизии
	bool** CollisMap = new bool*;
	// Спрайт заднего фона уровня
	sf::Texture BackgrTex;
	sf::Sprite Backgr;
	// Объект тайлсета
	sf::Texture TileSetTex;
	// Стартовая позиция игрока
	sf::Vector2f StartPos;
	// Количевство слоев
	sf::Int32 AmountLayers = 0;
	// Массив слоев
	world::FLayer* Layers = new world::FLayer[0];

public:
	// Инициализация уровня. Чтение мира из файлов и занос его в массив.
	void CreateWorld(sf::Uint32 LvlName);

	// Измение скорости в зависимости от препятствия  слева
	void LeftSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect);
	// Измение скорости в зависимости от препятствия  справа
	void RightSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect);
	// Измение скорости в зависимости от препятствия сверху
	void TopSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect);
	// Измение скорости в зависимости от препятствия снизу
	void DownSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect);

	// Получение коллизии по направлениям
	sf::Vector2f GetCorrectSpeed(EDirection XDirect, EDirection YDirect, sf::Vector2f Speed, sf::FloatRect PawnRect);

	// Функция отрисовки
	void DrawWorld(sf::RenderWindow& window, sf::Vector2f ViewCenter, sf::Vector2f ViewSize);

	// Возвращает стартовую позицию игрока
	sf::Vector2f GetStartPos();

	// Дает доступ к блоку карты колиззи
	bool& pBlockCollision(sf::Int32 i, sf::Int32 j);	

	// Проверяет есть ли под ногами земля
	bool isEarth(sf::Vector2f PawnPos, sf::FloatRect PawnRect);

	// Перевод из координат в тайлы 
	sf::Vector2i PointToTile(sf::Vector2f PointCoord);
	sf::Int32 XPointToTile(float x);
	sf::Int32 YPointToTile(float y);

	// Возвращает размер уровня в тайлах
	sf::Vector2i GetLvlSize();

	// Возвращает размер клетки в пикселях
	sf::Vector2i GetTileSize();
};

