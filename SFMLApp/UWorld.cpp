#include "UWorld.h" 

void UWorld::CreateWorld(sf::Uint32 LvlName)
{
	FParserXML ParserXML(std::to_string(LvlName));

	// Задаем размер уровня
	LvlSize.x = ParserXML.getLvlSize().x;
	LvlSize.y = ParserXML.getLvlSize().y;

	// Задаем размер тайла
	TileSize.x = ParserXML.getTileSize().x;
	TileSize.y = ParserXML.getTileSize().y;

	// Задаем размет тайлсета
	TileSetSize.x = ParserXML.getTileSetSize().x;
	TileSetSize.y = ParserXML.getTileSetSize().y;

	BackgrTex.loadFromFile(SpritePath + "SpaceBack.jpg");
	Backgr.setTexture(BackgrTex);

	TileSetTex.loadFromFile(SpritePath + "StarShipTiles.png");

	this->AmountLayers = ParserXML.getAmountLayer();

	Layers = new self::FLayer[AmountLayers];
	for (int count = 0; count < AmountLayers; count++) {
		Layers[count].Blocks.resize(LvlSize.y);
		for (int i = 0; i < LvlSize.y; i++) {
			Layers[count].Blocks[i].resize(LvlSize.x);
		}
	}

	for (int count = 0; count < AmountLayers; count++) {
		for (int i = 0; i < LvlSize.y; i++) {
			for (int j = 0; j < LvlSize.x; j++) {
				int TileId = ParserXML.getLayerElement(count, i, j);
				int XTileId, YTileId;
				YTileId = TileId / TileSetSize.x;
				XTileId = TileId % TileSetSize.x;
				Layers[count].Blocks[i][j].setTexture(TileSetTex);
				Layers[count].Blocks[i][j].setTextureRect(sf::IntRect(YTileId * TileSize.y, XTileId * TileSize.x, TileSize.x, TileSize.y));
				Layers[count].Blocks[i][j].setPosition(sf::Vector2f(j * TileSize.y, i * TileSize.x));
				if (TileId == 0)
					Layers[count].Blocks[i][j].setScale(sf::Vector2f(0, 0));
			}
		}
	}

}

void UWorld::DrawWorld(sf::RenderWindow& window)
{
	window.draw(Backgr);

	for (int count = 0; count < AmountLayers; count++) {
		for (int i = 0; i < LvlSize.y; i++) {
			for (int j = 0; j < LvlSize.x; j++) {
				window.draw(Layers[count].Blocks[i][j]);
			}
		}
	}
}

