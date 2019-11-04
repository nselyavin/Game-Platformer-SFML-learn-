#include "Headers\UWorld.h" 


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

	// Задаем путь к тайлсету
	sf::String PathToSet;
	PathToSet = ParserXML.getPathToSet();

	PathToSet.erase(0, 2);
	TileSetTex.loadFromFile("..\/Resource" + PathToSet);

	// Задаем количество слоев
	this->AmountLayers = ParserXML.getAmountLayer();

	// Задаем размеры массива спарйтов и карты коллизии 
	Layers = new world::FLayer[AmountLayers];
	for (int count = 0; count < AmountLayers; count++) {
		Layers[count].Blocks.resize(LvlSize.y);

		if (count == 0)
			CollisMap = new bool* [LvlSize.y];

		for (int i = 0; i < LvlSize.y; i++) {
			Layers[count].Blocks[i].resize(LvlSize.x);

			if (count == 0)
				CollisMap[i] = new bool[LvlSize.x];
		}
	}

	// Цикл заполнения слоев текстурами
	for (int count = 0; count < AmountLayers; count++) {
		for (int i = 0; i < LvlSize.y; i++) {
			for (int j = 0; j < LvlSize.x; j++) {
				// Айди тайла из тайлесета, для координат ректа 
				int TileId = ParserXML.getLayerElement(count, i, j);
				sf::Sprite tmpSprite;

				tmpSprite.setTexture(TileSetTex);

				// Проверка пустая ли клетка 
				if (TileId != 0) {
					TileId--;
					int XTileId, YTileId;
					YTileId = TileId / TileSetSize.x;
					XTileId = TileId - (YTileId * TileSetSize.x);

					tmpSprite.setTextureRect(sf::IntRect(XTileId * TileSize.x, YTileId * TileSize.y, TileSize.x, TileSize.y));
					tmpSprite.setPosition(sf::Vector2f(j * TileSize.x, i * TileSize.y));
				}
				else {
					tmpSprite.setTextureRect(sf::IntRect(-1, -1, 0, 0));
				}
				Layers[count].Blocks[i][j] = tmpSprite;
			}
		}
	}

	CollisMap = ParserXML.getCollisMap().CollisArr;
}	

// Корректировка скоростей от наличия блока и расстояния до него
void UWorld::LeftSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect)
{
	sf::Int32 y = YPointToTile(PawnRect.top);
	sf::Int32 y2 = YPointToTile(PawnRect.top + PawnRect.height / 2);
	sf::Int32 y3 = YPointToTile(PawnRect.top + PawnRect.height - 1);
	for (sf::Int32 i = 0; i > Speed; i--) {
		sf::Int32 x = XPointToTile(i + PawnRect.left - 1);
		if (CollisMap[y][x] == true || CollisMap[y2][x] == true || CollisMap[y3][x] == true) {
			Speed = i;
			break;
		}
	}
	Check = true;
}

void UWorld::RightSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect)
{
	sf::Int32 y = YPointToTile(PawnRect.top);
	sf::Int32 y2 = YPointToTile(PawnRect.top + PawnRect.height / 2);
	sf::Int32 y3 = YPointToTile(PawnRect.top + PawnRect.height - 1);
	for (sf::Int32 i = 0; i < Speed; i++) {
		sf::Int32 x = XPointToTile(i + PawnRect.left + PawnRect.width + 1);
		if (CollisMap[y][x] == true || CollisMap[y2][x] == true || CollisMap[y3][x] == true) {
			Speed = i;
			break;
		}
	}
	Check = true;
}

void UWorld::TopSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect)
{
	sf::Int32 x = XPointToTile(PawnRect.left+1);
	sf::Int32 x2 = XPointToTile(PawnRect.left + PawnRect.width - 1);
	for (sf::Int32 i = 0; i > Speed; i--) {
		sf::Int32 y = YPointToTile(i + PawnRect.top);
		if (CollisMap[y][x] == true || CollisMap[y][x2] == true) {
			Speed = i;
			break;
		}
	}
	Check = true;
}

void UWorld::DownSpeedLimmiter(float& Speed, bool& Check, sf::FloatRect PawnRect)
{
	sf::Int32 x = XPointToTile(PawnRect.left);
	sf::Int32 x2 = XPointToTile(PawnRect.left + PawnRect.width - 1);
	for (sf::Int32 i = 0; i < Speed; i++) {
		sf::Int32 y = YPointToTile(i + PawnRect.top + PawnRect.height);
		if (CollisMap[y][x] == true || CollisMap[y][x2] == true) {
			Speed = i;			
			break;
		}
	}
	Check = true;
}
 
sf::Vector2f UWorld::GetCorrectSpeed(EDirection XDirect, EDirection YDirect, sf::Vector2f Speed, sf::FloatRect PawnRect)
{
	// ToDo реализовать параллельность выполняемых проверок.

	bool bHoirizCheck = false, bVerticCheck = false;
	if (XDirect == EDirection::Left)
		LeftSpeedLimmiter(Speed.x, bVerticCheck, PawnRect);
	else if (XDirect == EDirection::Right)
		RightSpeedLimmiter(Speed.x, bVerticCheck, PawnRect);

	if (YDirect == EDirection::Top)
		TopSpeedLimmiter(Speed.y, bHoirizCheck, PawnRect);
	else if (YDirect == EDirection::Down)
		DownSpeedLimmiter(Speed.y, bHoirizCheck, PawnRect);

	return Speed;
}

struct VerticalsPoint {
	sf::Vector2f Left, Right;
};

struct SidePoint {
	sf::Vector2f Top, Middle, Bottom;
};

sf::Vector2i UWorld::PointToTile(sf::Vector2f PointCoord)
{
	sf::Int32 xTile, yTile;

	xTile = PointCoord.x / TileSize.x;
	yTile = PointCoord.y / TileSize.y;

	if (xTile < 0) xTile = 0;
	if (xTile > LvlSize.x) xTile = LvlSize.x - 1;
	if (yTile < 0) yTile = 0;
	if (yTile > LvlSize.y) yTile = LvlSize.y - 1;

	return sf::Vector2i(xTile, yTile);
}

sf::Int32 UWorld::XPointToTile(float x)
{
	x /= TileSize.x;
	if (x < 0) x = 0;
	if (x >= LvlSize.x) x = LvlSize.x - 1;
	return x;
}

sf::Int32 UWorld::YPointToTile(float y) {
	y /= TileSize.y;
	if (y < 0) y = 0;
	if (y >= LvlSize.y) y = LvlSize.y - 1;
	return y;
}

sf::Vector2i UWorld::GetLvlSize()
{
	return LvlSize;
}

sf::Vector2i UWorld::GetTileSize()
{
	return TileSize;
}

void UWorld::DrawWorld(sf::RenderWindow& window, sf::Vector2f ViewCenter, sf::Vector2f ViewSize)
{
	window.draw(Backgr);

	// Максимальная клетка, до которой может происходить отрисовка, чтобы избежать выхода из диапозона
	sf::Int32 maxRight = (sf::Int32(ViewCenter.x + ViewSize.x / 2) / TileSize.x), maxDown = (sf::Int32(ViewCenter.y + ViewSize.y / 2) / TileSize.y);

	for (sf::Int32 count = 0; count < AmountLayers; count++) {

		maxDown = (sf::Int32(ViewCenter.y + ViewSize.y / 2) / TileSize.y) + 1;
		if (maxDown > LvlSize.y) maxDown = LvlSize.y;

		for (sf::Int32 i = (sf::Int32(ViewCenter.y - ViewSize.y / 2) / TileSize.y) % LvlSize.y; i < maxDown; i++) {
			if (i < 0) i = 0;

			// Блокирует выход правой границы за диапозон
			maxRight = (sf::Int32(ViewCenter.x + ViewSize.x / 2) / TileSize.x) + 1;
			if (maxRight > LvlSize.x) maxRight = LvlSize.x;

			for (sf::Int32 j = (sf::Int32(ViewCenter.x - ViewSize.x / 2) / TileSize.y) % LvlSize.x; j < maxRight; j++) {
				if (j < 0) j = 0;

				// Если отрисовывать нечего, то не отрисовывать. Logic
				if (Layers[count].Blocks[i][j].getPosition().y != -1)
					window.draw(Layers[count].Blocks[i][j]);
			}
		}
	}
}

sf::Vector2f UWorld::GetStartPos()
{
	return StartPos;
}

bool& UWorld::pBlockCollision(sf::Int32 i, sf::Int32 j)
{
	return CollisMap[i][j];
}

bool UWorld::isEarth(sf::Vector2f PawnPos, sf::FloatRect PawnRect)
{
	sf::Int32 x = XPointToTile(PawnRect.left);
	sf::Int32 x2 = XPointToTile(PawnRect.left + PawnRect.width);
	sf::Int32 y = YPointToTile(PawnRect.top + PawnRect.height);

	if (CollisMap[y][x] || CollisMap[y][x2])
		return true;
	
	return false;
}

