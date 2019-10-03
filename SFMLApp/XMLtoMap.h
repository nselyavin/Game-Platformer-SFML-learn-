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

struct FVector2i {int x;	int y;};

struct FLayer
{
	std::string name = "";
	//int** arr;
	std::vector <std::vector<int>> arr;
};

struct FLevelStruct
{
	// Êîëè÷åñòâî êëåòîê íà óðîâíå
	FVector2i LvlTiles;		

	// Ðàçìåð â ïèêñåëÿõ îäíîé êëåòêè
	FVector2i LvlSizeTile;

	// Êîëè÷åñòâî ñëîåâ íà êàðòå
	int AmountLayer = 0;

	// Ñòàðòîâàÿ ïîçèöèÿ èãðîêà
	float StartPos;
};


class FParserXML
{
private:
	std::string LvlName;
	FLevelStruct LevelStruct;
	// ToDo ïåðåäåëàòü âñå îòíîñèòåëüíî îòäåëüíîé ñòðóêòóðû, à íå ïåðåìåííîé LevelStruct
	FLayer* Layers = new FLayer[LevelStruct.AmountLayer];
	int* Arr = new int[3];
	// Òåêóùèé ñëîé äëÿ çàïîëíåíèÿ
	int CurrLayer = -1;
	// Èíäåêñû òåêóþùåé êëåòêè äëÿ çàïîëíåíèÿ
	int i = 0, j = 0;
	
public:
	FParserXML(std::string LvlName);

	~FParserXML() {};

	
	std::string ValueByTag(std::string& line, const char* tag);

	// Óâåëè÷åíèå îáçåãî êîëè÷åñòâà ñëîåâ íà óðîâíå
	FLayer* AddLayer(FLayer *Layer, const int Amount);

	// Âîçðàùàåò êîëè÷åñòâî êëåòîê íå óðîâíå
	FVector2i getLvlTiles();

	// Âîçâðàùàåò ðàçìåð îäíîé êëåòêè
	FVector2i getSizeTile();

	// Âîâçðàùàåò ñòðóêòóðà ñëîÿ ïî id
	const FLayer& getLayer(int idLayer);

	// Âîçâðàùàåò êîëè÷åñòâî ñëîåâ íà óðîâíå
	const int getAmountLayer();

	// Âîçðàùàåò êëåòêó êàðòû ïî èíäåêñàì â óêàçàííîì ñëîå
	const int getLayerElement(int idLayer, int i, int j);
};


