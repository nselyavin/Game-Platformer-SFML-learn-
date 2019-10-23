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
	bool Collision = false;
	std::vector <std::vector<int>> arr;
};

struct FCollisMap
{
	bool** CollisArr = new bool*;
};

struct FLevelStruct
{
	// Путь к тайлсету
	std::string PathToSet;

	// Размер ТайлСета
	FVector2i TileSetSize;

	// Размер карты в тайлах
	FVector2i LvlSize;		

	// Рразмер одного тайла в пикселях
	FVector2i TileSize;

	// Количество тайлов в тайлсете
	int AmountTiles = 0;

	// Количество Слоев
	int AmountLayer = 0;

	// Стартовая точка игрока
	float StartPos;
	float FinishPos;
};


class FParserXML
{
private:
	// Название уровня
	std::string LvlName;
	// Объявление структуры уровня, содержащая параметры уровня
	FLevelStruct LevelStruct; 
	// Карта колизии уровня
	FCollisMap CollisMap;
	// Массив слове уровня
	FLayer* Layers = new FLayer[LevelStruct.AmountLayer];
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

	// Возвращает путь до картинки тайлсета
	const std::string getPathToSet();

	// Возращает количество клеток не уровне
	FVector2i getLvlSize();

	// Возвращает размер одной клетки
	FVector2i getTileSize();

	// Возвращает размер тайлсета в тайлах
	FVector2i getTileSetSize();

	// Вовзращает структура слоя по id
	const FLayer& getLayer(int idLayer);

	// Возвращает объект коллизии
	const FCollisMap getCollisMap();

	// Возвращает количество слоев на уровне
	const int getAmountLayer();

	// озращает клетку карты по индексам в указанном слоев
	const int getLayerElement(int idLayer, int i, int j);

	// Возвращает статус коллизии слоя по id
	const bool getLayerCollis(int idLayer);
};


