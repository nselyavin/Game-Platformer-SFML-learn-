#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

struct FVector2i {int x;	int y;};

struct FLayer
{
	std::string name = "";
	//int** arr;
	std::vector <std::vector<int>> arr;
};

struct FLevelStruct
{
	// Количество клеток на уровне
	FVector2i LvlTiles;		

	// Размер в пикселях одной клетки
	FVector2i LvlSizeTile;

	// Количество слоев на карте
	int AmountLayer = 0;

	// Стартовая позиция игрока
	float StartPos;
};


class FParserXML
{
private:
	std::string LvlName;
	FLevelStruct LevelStruct;
	// ToDo переделать все относительно отдельной структуры, а не переменной LevelStruct
	FLayer* Layers = new FLayer[LevelStruct.AmountLayer];
	int* Arr = new int[3];
	// Текущий слой для заполнения
	int CurrLayer = -1;
	// Индексы текующей клетки для заполнения
	int i = 0, j = 0;
	
public:
	FParserXML(std::string LvlName);

	~FParserXML() {};

	
	std::string ValueByTag(std::string& line, const char* tag);

	// Увеличение обзего количества слоев на уровне
	FLayer* AddLayer(FLayer *Layer, const int Amount);

	// Возращает количество клеток не уровне
	FVector2i getLvlTiles();

	// Возвращает размер одной клетки
	FVector2i getSizeTile();

	// Вовзращает структура слоя по id
	const FLayer& getLayer(int idLayer);

	// Возвращает количество слоев на уровне
	const int getAmountLayer();

	// Возращает клетку карты по индексам в указанном слое
	const int getLayerElement(int idLayer, int i, int j);
};


