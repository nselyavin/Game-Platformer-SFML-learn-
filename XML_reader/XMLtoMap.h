#pragma once

#include <string>
#include <fstream>
#include <algorithm>

struct FVector2i {int x;	int y;};

struct FLayer
{
	std::string name;
	int** arr = new int*;
};

struct FLevelStruct
{
	// Количество клеток на уровне
	FVector2i LvlTiles;		

	// Размер в пикселях одной клетки
	FVector2i LvlSizeTile;

	// Количество слоев на карте
	int NumbLayer;

	// Двумерный массив каждого слоя
	FLayer* Layers = new FLayer;

	// Стартовая позиция игрока
	float StartPos;
};


class FParserXML
{
private:
	std::string LvlName;
	FLevelStruct LevelStruct;
	
public:
	FParserXML(std::string LvlName);

	template<class T>
	T ValueByTag(const std::string& tag);

	// Возращает количество клеток не уровне
	FVector2i getLvlTiles();

	// Возвращает размер одной клетки
	FVector2i getSizeTile();

	// Вовзращает структура слоя по id
	const FLayer& getLayer(int idLayer);

	// Возращает клетку карты по индексам в указанном слое
	const int getLayerElement(int idLayer, int i, int j);
};


