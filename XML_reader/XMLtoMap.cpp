#include "XMLtoMap.h"

FParserXML::FParserXML(std::string LvlName)
{
	std::ifstream ifsLvl;
	ifsLvl.open(LvlName + ".tmx");

	std::string line;

	if (!ifsLvl.is_open())
		printf("File opening faled");

	while (!ifsLvl.eof()) {
		getline(ifsLvl, line);

		std::string::size_type FindRes = std::string::npos;

		FindRes = line.find("<map");
		if (FindRes != std::string::npos) {
			LevelStruct.LvlTiles.x = std::stoi(ValueByTag(line, "width"));
			LevelStruct.LvlTiles.y = std::stoi(ValueByTag(line, "height"));
			LevelStruct.LvlSizeTile.x = std::stoi(ValueByTag(line, "tilewidth"));
			LevelStruct.LvlSizeTile.y = std::stoi(ValueByTag(line, "tileheight"));
		}
		
	}

	ifsLvl.close();	
}


std::string FParserXML::ValueByTag(std::string& line, const char* tag)
{
	// ToDo Написать реализацию поиска значения по тегу
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