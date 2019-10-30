#include "Headers\APlayerPawn.h"


APlayerPawn::APlayerPawn()
{
	// Инициализация основных параметров пешки
	this->Health = 3;
	this->Mass = 44;
	this->bAlive = true;
	this->bOnEarth = true;
	this->Speed.x = 0;
	this->Speed.y = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPose = 0;
	XDirection = EDirection::Right;
	YDirection = EDirection::Left;
}

sf::Int32 APlayerPawn::CreatePawn(float x, float y)
{
	// Сделать, что бы коллизия игрока была 32 на 64 пикселей. И соотвестующая моделька.

	// Инициализация основных параметров пешки
	this->ASprite.setPosition(x, y);
	this->Health = 3;
	this->Mass = 50;
	this->bOnEarth = true;
	this->bAlive = true;
	this->Speed.x = 0;
	this->Speed.y = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPose = 0;

	// Загрузка текстуры спрайта
	if (!ATexture.loadFromFile(SpritePath + "DbgDed.png"))
		return EEndStatus::FileLoadFaled;

	ASprite.setTexture(ATexture);
	ASprite.setTextureRect(sf::IntRect(0, 0, 32, 64));

	XDirection = EDirection::Right;
	YDirection = EDirection::Left;

	return EEndStatus::StartGame;
}

void APlayerPawn::DrawPawn(sf::RenderWindow& window)
{
	window.draw(ASprite); 
	
}

void APlayerPawn::ChangeSelfSpeed(EActionList Action)
{
	// ToDo Сделать движение плавным и затухающим

	if (Action == EActionList::Move_Left) {
		Speed.x = -10;
	} 
	else if (Action == EActionList::Move_Right) {
		Speed.x = 10;
	}
	else if (Action == EActionList::Jump_Left || Action == EActionList::Jump_Right) {
		if (bOnEarth)
			Speed.y = -20;
	}
	else if (Action == EActionList::Idle_Left || Action == EActionList::Idle_Right) {
		Speed.x = 0;
	} 

	SetStance(Action);
}

void APlayerPawn::MoveModificators() 
{
	Speed.y += Mass * g;

	if (Speed.x < 0) XDirection = EDirection::Left;
	else if (Speed.x > 0) XDirection = EDirection::Right;

	if (Speed.y < 0) YDirection = EDirection::Top;
	else if (Speed.y > 0) YDirection = EDirection::Down;
	else YDirection = EDirection::Nowhere;

}

void APlayerPawn::MovePawn()
{
	ASprite.move(Speed.x, Speed.y);
}

void APlayerPawn::setPosition(sf::Vector2f Pos)
{
	ASprite.setPosition(Pos);
}

void APlayerPawn::setSpeed(sf::Vector2f Speed)
{
	this->Speed.x = Speed.x;
	this->Speed.y = Speed.y;
}

void APlayerPawn::SetStance(EActionList Action)
{
	// ToDo Реализовать зедержку анимации
	switch (Action) {
	case EActionList::Move_Left:	
		// Смена текущего кадра в зависимости от времени
		CurrPose = (CurrPose + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(32 * CurrPose, 64 * 2, 32, 64));
		break;
	case EActionList::Move_Right:
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



const sf::FloatRect APlayerPawn::GetPawnRect()
{	
	PawnRect = ASprite.getGlobalBounds(); 
	return PawnRect; 
}

bool APlayerPawn::isAlive() { return bAlive; }

bool& APlayerPawn::pOnEarthStatus()
{
	return bOnEarth;
}

const sf::Sprite APlayerPawn::GetSprite() { return ASprite; }

const sf::Texture APlayerPawn::GetTexture() { return ATexture; }

const sf::Vector2f APlayerPawn::GetPos(){ return ASprite.getPosition(); }

const sf::Int32 APlayerPawn::GetHealth(){ return Health; }

const EDirection APlayerPawn::GetXDirection(){ return XDirection; }

const sf::Vector2f APlayerPawn::GetSpeed(){	return Speed; }

const EDirection APlayerPawn::GetYDirection(){ return YDirection; }
