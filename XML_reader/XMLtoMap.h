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
	//  оличество клеток на уровне
	FVector2i LvlTiles;		

	// –азмер в пиксел€х одной клетки
	FVector2i LvlSizeTile;

	//  оличество слоев на карте
	int NumbLayer = 0;

	// —тартова€ позици€ игрока
	float StartPos;
};


class FParserXML
{
private:
	std::string LvlName;
	FLevelStruct LevelStruct;
	// ToDo переделать все относительно отдельной структуры, а не переменной LevelStruct
	FLayer* Layers = new FLayer[0];
	
public:
	FParserXML(std::string LvlName);

	~FParserXML() {};

	
	std::string ValueByTag(std::string& line, const char* tag);

	// ¬озращает количество клеток не уровне
	FVector2i getLvlTiles();

	// ¬озвращает размер одной клетки
	FVector2i getSizeTile();

	// ¬овзращает структура сло€ по id
	const FLayer& getLayer(int idLayer);

	// ¬озращает клетку карты по индексам в указанном слое
	const int getLayerElement(int idLayer, int i, int j);
};


