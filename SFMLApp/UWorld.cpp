#include "UWorld.h" 

void UWorld::CreateWorld(sf::Uint32 LvlName)
{
	//FParserXML ParserXML(std::to_string(LvlName));

//Layers = new FLayer[ParserXML.getAmountLayer];


	BackgrTex.loadFromFile(SpritePath + "SpaceBack.jpg");
	Backgr.setTexture(BackgrTex);
	//Backgr.setScale(Backgr.getScale().x * 2, Backgr.getScale().y * 4);
}

void UWorld::DrawWorld(sf::RenderWindow& window)
{
	window.draw(Backgr);
}

