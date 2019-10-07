/*
	Парсер по файлам карт с расширение .tmx.
	Проходит по всем строчкам файла. Ищет подстрокой нужный блок. Затем функцией получается значение запрошенного тега.
	Может считывать разные слои. Но пока нету чтения для объектов и ключеввых точек карты.
*/

#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "GameConst.h"

struct FVector2i {int x;	int y;};

struct FLayer
{
	std::string name = "";
	std::vector <std::vector<int>> arr;
};

struct FLevelStruct
{
	// Размер карты в тайлах
	FVector2i LvlTiles;		

	// Рразмер одного тайла в пикселях
	FVector2i LvlSizeTile;

	// Количество Слоев
	int AmountLayer = 0;

	// Стартовая точка игрока
	float StartPos;
	float FinishPos;
};


class FParserXML
{
private:
	std::string LvlName;
	FLevelStruct LevelStruct; 
	FLayer* Layers = new FLayer[LevelStruct.AmountLayer];
	int* Arr = new int[3];
	// Текущий слой для заполнения
	int CurrLayer = -1;
	// Индексы текующей клетки для заполнения
	int i = 0, j = 0;
	
public:
	FParserXML(std::string LvlName);

	~FParserXML();
	
	// Возвращает значение в строке по тегу
	std::string getValueByTag(std::string& line, const char* tag);

	// Увеличение общего количества слоев на уровне
	FLayer* AddLayer(FLayer *Layer, const int Amount);

	// Возращает количество клеток не уровне
	FVector2i getLvlTiles();

	// Возвращает размер одной клетки
	FVector2i getSizeTile();

	// Вовзращает структура слоя по id
	const FLayer& getLayer(int idLayer);

	// Возвращает количество слоев на уровне
	const int getAmountLayer();

	// озращает клетку карты по индексам в указанном слоев
	const int getLayerElement(int idLayer, int i, int j);
};


