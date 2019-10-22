#include "APlayerPawn.h"


APlayerPawn::APlayerPawn()
{
	// Инициализация основных параметров пешки
	this->Health = 3;
	this->Mass = 44;
	this->bAlive = true;
	this->SpeedX = 0;
	this->SpeedY = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPose = 0;
}

int APlayerPawn::CreatePawn(float x, float y)
{
	// Сделать, что бы коллизия игрока была 32 на 64 пикселей. И соотвестующая моделька.

	// Инициализация основных параметров пешки
	this->ASprite.setPosition(x, y);
	this->Health = 3;
	this->Mass = 44;
	this->bAlive = true;
	this->SpeedX = 0;
	this->SpeedY = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPose = 0;

	// Загрузка текстуры спрайта
	if (!ATexture.loadFromFile(SpritePath + "DbgDed.png"))
		return EEndStatus::FileLoadFaled;

	ASprite.setTexture(ATexture);
	ASprite.setTextureRect(sf::IntRect(0, 0, 32, 64));

	return EEndStatus::StartGame;
}

void APlayerPawn::DrawPawn(sf::RenderWindow& window)
{
	window.draw(ASprite); 
	
}

void APlayerPawn::ChangeSelfSpeed(EActionList Action)
{
	if (Action == EActionList::Move_Left) {
		SpeedX = -10;
	} 
	else if (Action == EActionList::Move_Right) {
		SpeedX = 10;
	}
	else if (Action == EActionList::Jump_Left || Action == EActionList::Jump_Right) {
		if (MoveDeny.Down)
			SpeedY = -10;
	}
	else if (Action == EActionList::Idle_Left || Action == EActionList::Idle_Right) {
		SpeedX = 0;
	}

	SetStance(Action);
}

void APlayerPawn::MovePawn()
{
	// ToDo Сделать движение плавным и затухающим

	//SpeedY += Mass * g;
	PawnRect = ASprite.getGlobalBounds();

	if (MoveDeny.Left) {
		if (SpeedX < 0) {
			SpeedX = 0;
		}
		ASprite.setPosition((floor(ASprite.getPosition().x / 32) + 1) * 32, ASprite.getPosition().y);
	}
	if (MoveDeny.Right) {
		if (SpeedX > 0) {
			SpeedX = 0;
		}
	}
	if (MoveDeny.Top) {
		if (SpeedY < 0) {
			SpeedY = 0;
		}
	}
	if (MoveDeny.Down) {
		if (SpeedY > 0) {
			SpeedY = 0;
		}
	}
	ASprite.move(SpeedX, SpeedY);
}

void APlayerPawn::setPosition(sf::Vector2f Pos)
{
	ASprite.setPosition(Pos);
}



void APlayerPawn::SetStance(EActionList Action)
{
	// ToDo Реализовать зедержку анимации
	switch (Action) {
	case EActionList::Move_Left:	
		XDirection = -1;
		// Смена текущего кадра в зависимости от времени
		CurrPose = (CurrPose + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(32 * CurrPose, 64 * 2, 32, 64));
		break;

	case EActionList::Move_Right:
		XDirection = 1;
		// Смена текущего кадра в зависимости от времени
		CurrPose = (CurrPose + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(32 * CurrPose, 64 * 1, 32, 64));
		break;

	case EActionList::Jump_Left:                 
		ASprite.setTextureRect(sf::IntRect(96, 0, 32, 64));
		break;

	case EActionList::Jump_Right:
		ASprite.setTextureRect(sf::IntRect(64, 0, 32, 64));
		break;

	case EActionList::Idle_Left:
		ASprite.setTextureRect(sf::IntRect(32, 0, 32, 64));
		CurrPose = 0;
		break;

	case EActionList::Idle_Right:
		ASprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
		CurrPose = 0;
		break;
	}
	Clock.restart();
}

const bool APlayerPawn::isAlive()
{
	if (Health > 0)
		return true;
	return false;
}


const sf::Sprite& APlayerPawn::GetSprite()
{
	return ASprite;
}

const sf::Texture& APlayerPawn::GetTexture()
{
	return ATexture;
}

const sf::FloatRect& APlayerPawn::GetPawnRect()
{
	PawnRect = ASprite.getGlobalBounds();

	return PawnRect;
}

const sf::Vector2f& APlayerPawn::GetPos()
{
	return ASprite.getPosition();
}

const int APlayerPawn::GetHealth()
{
	return Health;
}

const sf::Int8 APlayerPawn::GetXDirection()
{
	return XDirection;
}

const sf::Vector2f APlayerPawn::GetSpeed()
{
	sf::Vector2f Speed;
	Speed.x = SpeedX;
	Speed.y = SpeedY;
	return Speed;
}

FMoveDeny& APlayerPawn::getMoveDeny()
{
	return MoveDeny;
}