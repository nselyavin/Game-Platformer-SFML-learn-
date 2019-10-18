#include "UWorld.h" 

UWorld::~UWorld()
{
	delete[] Layers;
}

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

	// ToDo считывать стартовую позицию из парсера
	StartPos.x = 384.f;
	StartPos.y = 100.f;

	// Задаем задний фон уровня
	// ToDo переместить название в переменную, и вызывать под нужды уровня
	BackgrTex.loadFromFile(SpritePath + "SpaceBack.jpg");
	Backgr.setTexture(BackgrTex);

	sf::String PathToSet;
	PathToSet = ParserXML.getPathToSet();

	PathToSet.erase(0, 2);
	TileSetTex.loadFromFile("..\/Resource" + PathToSet);

	this->AmountLayers = ParserXML.getAmountLayer();

	Layers = new self::FLayer[AmountLayers];
	for (int count = 0; count < AmountLayers; count++) {
		Layers[count].Blocks.resize(LvlSize.y);
		for (int i = 0; i < LvlSize.y; i++) {
			// Нужен, чтобы в дальнешейм не хранить в массиве спрайты без текстур.
			int tmpSize = 0;
			for (int j = 0; j < LvlSize.x; j++){
				if (ParserXML.getLayerElement(count, i, j) != 0) {
					tmpSize++;
				}
			}
			Layers[count].Blocks[i].resize(tmpSize);
		}
	}

	// Цикл заполнения слоев текстурами
	for (int count = 0; count < AmountLayers; count++) {
		for (int i = 0; i < LvlSize.y; i++) {
			for (int j = 0; j < LvlSize.x; j++) {
				int TileId = ParserXML.getLayerElement(count, i, j);
				if (TileId != 0) {
					TileId--;
					int XTileId, YTileId;
					YTileId = TileId / TileSetSize.x;
					XTileId = TileId - (YTileId * TileSetSize.x);

					sf::Sprite tmpSprite;
					
					tmpSprite.setTexture(TileSetTex);
					tmpSprite.setTextureRect(sf::IntRect(XTileId * TileSize.x, YTileId * TileSize.y, TileSize.x, TileSize.y));
					tmpSprite.setPosition(sf::Vector2f(j * TileSize.x, i * TileSize.y));

					Layers[count].Blocks[i].push_back(tmpSprite);
				}
			}
		}
	}
}

void UWorld::DrawWorld(sf::RenderWindow& window)
{
	window.draw(Backgr);

	for (int count = 0; count < AmountLayers; count++) {
		for (int i = 0; i < LvlSize.y; i++) {
			for (int j = 0; j < Layers[count].Blocks[i].size(); j++) {
				window.draw(Layers[count].Blocks[i][j]);
			}
		}
	}
}

sf::Vector2f UWorld::getStartPos()
{
	return StartPos;
}

