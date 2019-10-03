#include "XMLtoMap.h"
#include <iostream>

FParserXML::FParserXML(std::string LvlName)
{
	std::ifstream ifsLvl;
	std::string line;

	ifsLvl.open(LvlName + ".tmx");

	this->LvlName = LvlName;

	if (!ifsLvl.is_open())
		printf("File opening faled");

	while (!ifsLvl.eof()) {
		// Считывание из файла
		getline(ifsLvl, line);

		std::string::size_type FindRes = std::string::npos;

		FindRes = line.find("<map");
		if (FindRes != std::string::npos) {
			// Получаем по тегу размеры карты
			LevelStruct.LvlTiles.x = std::stoi(ValueByTag(line, "width"));
			LevelStruct.LvlTiles.y = std::stoi(ValueByTag(line, "height"));
			
			// Получаем по тегу размер тайла
			LevelStruct.LvlSizeTile.x = std::stoi(ValueByTag(line, "tilewidth"));
			LevelStruct.LvlSizeTile.y = std::stoi(ValueByTag(line, "tileheight"));
		}	

		FindRes = line.find("<layer");
		if (FindRes != std::string::npos) {
			Layers = AddLayer(Layers, LevelStruct.AmountLayer);
			LevelStruct.AmountLayer++;		
			CurrLayer++;								  
			i = 0;										  
			j = 0;										  
		}

		FindRes = line.find("<tile");
		if (FindRes != std::string::npos) {
			FindRes = line.find("<tileset");
			if (FindRes == std::string::npos) {
				Layers[CurrLayer].arr[i][j] = std::stoi(ValueByTag(line, "gid"));
				i = i + ((j + 1) / LevelStruct.LvlTiles.x);
				j = (j + 1) % LevelStruct.LvlTiles.x;
			}
		}

		// ToDo Парсер для объектов

	} 

	ifsLvl.close();	
}


std::string FParserXML::ValueByTag(std::string& line, const char* tag)
{
	std::string Value = "";
	std::string::size_type res = std::string::npos;

	res = line.find(tag);
	if (res == std::string::npos)
		return "0";

	res = line.find_first_of('\"', res);
	
	for (size_t i = res + 1; line[i] != '\"'; i++) {
		Value.push_back(line[i]);
	}

	return Value;
}

FLayer* FParserXML::AddLayer(FLayer* Layer, const int Amount)
{
	
	if (Amount == 0) {
		Layer = new FLayer[Amount + 1];
	}
	else {
		FLayer* tmp = new FLayer[Amount + 1];


		for (int i = 0; i < Amount; i++) {
			tmp[i] = Layer[i];
		}

		delete[] Layer;

		Layer = tmp;
	}
	
	Layer[Amount].arr.resize(LevelStruct.LvlTiles.y);

	for (int i = 0; i < LevelStruct.LvlTiles.y; i++) {
		Layer[Amount].arr[i].resize(LevelStruct.LvlTiles.x);
	}

	return Layer;
}

FVector2i FParserXML::getLvlTiles()
{
	return LevelStruct.LvlTiles;
}

FVector2i FParserXML::getSizeTile()
{
	return LevelStruct.LvlSizeTile;
}

const FLayer& FParserXML::getLayer(int idLayer)
{
	return Layers[idLayer];
}

const int FParserXML::getAmountLayer() {
	return LevelStruct.AmountLayer;
}

const int FParserXML::getLayerElement(int idLayer, int i, int j)
{
	return Layers[idLayer].arr[i][j];
}
