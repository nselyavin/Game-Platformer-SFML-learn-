#include "XMLtoMap.h"

FParserXML::FParserXML(std::string LvlName)
{
	std::ifstream ifsLvl(LvlName + ".tmx");
	std::string line;

	if (!ifsLvl.is_open())
		printf("File opening faled");

	while (!ifsLvl.eof()) {
		getline(ifsLvl, line);

		if (line.find("map") == true) {

		}
		
	}
}

template<class T>
T FParserXML::ValueByTag(const std::string& tag)
{
	// ToDo Написать реализацию поиска значения по тегу
	return T;
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
	return LevelStruct.Layers[idLayer];
}

const int FParserXML::getLayerElement(int idLayer, int i, int j)
{
	return LevelStruct.Layers[idLayer].arr[i][j];
}