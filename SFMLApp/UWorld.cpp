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

	// ToDo считывать стартовую позицию из парсера
	StartPos.x = 384.f;
	StartPos.y = 96.f;

	// Задаем задний фон уровня
	// ToDo переместить название в переменную, и вызывать под нужды уровня
	BackgrTex.loadFromFile(SpritePath + "SpaceBack.jpg");
	Backgr.setTexture(BackgrTex);

	sf::String PathToSet;
	PathToSet = ParserXML.getPathToSet();

	PathToSet.erase(0, 2);
	TileSetTex.loadFromFile("..\/Resource" + PathToSet);

	this->AmountLayers = ParserXML.getAmountLayer();

	Layers = new world::FLayer[AmountLayers];
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

	CollisMap = new bool*[LvlSize.y];
	for (int i = 0; i < LvlSize.y; i++) {
		CollisMap[i] = new bool[LvlSize.x];
	}

	CollisMap = ParserXML.getCollisMap().CollisArr;
	
	for (int i = 0; i < LvlSize.y; i++) {
		for (int j = 0; j < LvlSize.x; j++) {
			printf("%d ", CollisMap[i][j]);
		}
		printf("\n");
	}

}

struct VerticalsPoint {
	sf::Vector2f Left, Right;
};

struct SidePoint {
	sf::Vector2f Top, Middle, Bottom;
};


sf::Vector2i UWorld::PointToTile(sf::Vector2f PointCoord)
{
	int xTile, yTile;

	xTile = PointCoord.x / TileSize.x;
	yTile = PointCoord.y / TileSize.y;

	return sf::Vector2i(xTile, yTile);
}


void UWorld::getCollisDirect(sf::FloatRect PawnRect, bool& bUp, bool& bDown, bool& bLeft, bool& bRight)
{
	bUp = false;
	bDown = false;
	bLeft = false;
	bRight = false;

	VerticalsPoint Top, Under;
	SidePoint Left, Right;

	// Верхние точки
	Top.Left = sf::Vector2f(PawnRect.left, PawnRect.top - 1);
	Top.Right = sf::Vector2f(PawnRect.left + PawnRect.width - 1, PawnRect.top - 1);
	
	// Нижние точки 
	Under.Left = sf::Vector2f(PawnRect.left, PawnRect.top + PawnRect.height + 1);
	Under.Right = sf::Vector2f(PawnRect.left + PawnRect.width - 1, PawnRect.top + PawnRect.height);

	// Левые точки
	Left.Top = sf::Vector2f(PawnRect.left - 1, PawnRect.top);
	Left.Middle = sf::Vector2f(PawnRect.left - 1, PawnRect.top + PawnRect.height / 2 );
	Left.Bottom = sf::Vector2f(PawnRect.left - 1, PawnRect.top + PawnRect.height - 1);

	// Правые точки
	Right.Top = sf::Vector2f(PawnRect.left + PawnRect.width, PawnRect.top);
	Right.Middle = sf::Vector2f(PawnRect.left + PawnRect.width, PawnRect.top + PawnRect.height / 2);
	Right.Bottom = sf::Vector2f(PawnRect.left  + PawnRect.width, PawnRect.top + PawnRect.height - 1);

	// Запрет движения вверх 
	if ((PointToTile(Top.Left).y < 0) || 
		CollisMap[PointToTile(Top.Left).y][PointToTile(Top.Left).x] == true ||
		CollisMap[PointToTile(Top.Right).y][PointToTile(Top.Right).x] == true)
		bUp = true;
	
	// Запрет движения вниз
	if ((PointToTile(Under.Left).y > LvlSize.y - 1) ||
		CollisMap[PointToTile(Under.Left).y][PointToTile(Under.Left).x] == true ||
		CollisMap[PointToTile(Under.Right).y][PointToTile(Under.Right).x] == true)
		bDown = true;

	// Запрет движения влево
	if ((PointToTile(Left.Top).x < 0) ||
		CollisMap[PointToTile(Left.Top).y][PointToTile(Left.Top).x] == true ||
		CollisMap[PointToTile(Left.Middle).y][PointToTile(Left.Middle).x] == true ||
		CollisMap[PointToTile(Left.Bottom).y][PointToTile(Left.Bottom).x] == true)
		bLeft = true;
	
	// Запрет движения вправо
	if ((PointToTile(Right.Top).x > LvlSize.x - 1) ||
		CollisMap[PointToTile(Right.Top).y][PointToTile(Right.Top).x] == true ||
		CollisMap[PointToTile(Right.Middle).y][PointToTile(Right.Middle).x] == true ||
		CollisMap[PointToTile(Right.Bottom).y][PointToTile(Right.Bottom).x] == true)
		bRight = true;
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

