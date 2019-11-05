#include "Headers\APlayerPawn.h"

#include <iostream>

APlayerPawn::APlayerPawn()
{
	// Инициализация основных параметров пешки
	this->Health = 3;
	this->Mass = 44;
	this->bOnEarth = true;
	this->Speed.x = 0;
	this->Speed.y = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPoseFrame = 0;
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
	this->Speed.x = 0;
	this->Speed.y = 0;
	this->Gravity = 10;
	this->delay = 100;
	this->CurrPoseFrame = 0;

	// Загрузка текстуры спрайта
	if (!ATexture.loadFromFile(SpritePath + "DbgBoy.png"))
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

void APlayerPawn::MoveLeft() {
	if (Speed.x > -12)
		Speed.x -= 3;
	Action = EActionList::Move_Left;
}

void APlayerPawn::MoveRight() {
	if (Speed.x < 12)
		Speed.x += 3;
	Action = EActionList::Move_Right;
}

void APlayerPawn::Jump() {
	if (bOnEarth)
		Speed.y = -17;
	Action = EActionList::Jump_Right;
}

void APlayerPawn::Breaking(){
	// Сила трения
	if (Speed.x > 0)
		Speed.x -= 3;
	else if (Speed.x < 0)
		Speed.x += 3;
}


void APlayerPawn::MoveModificators() 
{
	// Гравитация
	Speed.y += 1;

	std::cout << Speed.x << " " << XDirection << std::endl;
	

	if (Speed.x < 0) XDirection = EDirection::Left;
	else if (Speed.x > 0) XDirection = EDirection::Right;

	if (Speed.y < 0) YDirection = EDirection::Top;
	else if (Speed.y > 0) YDirection = EDirection::Down;
	else YDirection = EDirection::Nowhere;
}

void APlayerPawn::AcceptMove()
{
	ASprite.move(Speed.x, Speed.y);
	ChangePose();
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

void APlayerPawn::setHealth(sf::Int32 Health)
{
	this->Health = Health;
}



void APlayerPawn::ChangePose()
{
	// ToDo Реализовать зедержку анимации
	switch (Action) {
	case EActionList::Move_Left:	
		// Смена текущего кадра в зависимости от времени
		CurrPoseFrame = (CurrPoseFrame + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(32 * CurrPoseFrame, 64 * 2, 32, 64));
		break;
	case EActionList::Move_Right:
		// Смена текущего кадра в зависимости от времени
		CurrPoseFrame = (CurrPoseFrame + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(32 * CurrPoseFrame, 64 * 1, 32, 64));
		break;

	default:
		// Одна формула на две стороны стояния
		ASprite.setTextureRect(sf::IntRect(16 + (16 * XDirection), 0, 32, 64));
		CurrPoseFrame = 0;

		break;
	}

	if (!bOnEarth) {
		if (XDirection == EDirection::Left)
			Action = EActionList::Jump_Right;
		else
			Action = EActionList::Jump_Left;

		ASprite.setTextureRect(sf::IntRect(80 + (16 * XDirection), 0, 32, 64));
		ASprite.setTextureRect(sf::IntRect(64, 0, 32, 64));
	}
	Clock.restart();
}



const sf::FloatRect APlayerPawn::GetPawnRect()
{	
	PawnRect = ASprite.getGlobalBounds(); 
	return PawnRect; 
}

bool APlayerPawn::isAlive() { 
	if (Health <= 0)
		return  false;
		
	return true;
}

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
