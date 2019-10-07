#include "APlayerPawn.h"


int APlayerPawn::CreatePawn(float x, float y)
{
	// Сделать, что бы коллизия игрока была 32 на 64 пикселей. И соотвестующая моделька.

	// Инициализация основных параметров пешки
	this->ASprite.setPosition(x, y);
	this->Health = 3;
	this->bAlive = true;
	this->SpeedX = 8;
	this->SpeedY = 0;
	this->delay = 100;

	// Загрузка текстуры спрайта
	if (!ATexture.loadFromFile(SpritePath + "Boy_Sprites.png"))
		return EEndStatus::FileLoadFaled;

	ASprite.setTexture(ATexture);
	ASprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	CurrPose = 0;

	return EEndStatus::StartGame;
}

void APlayerPawn::DrawPawn(sf::RenderWindow& window)
{
	window.draw(ASprite); 
	
}

void APlayerPawn::MovePawn()
{
	// ToDo Сделать движение плавный и затухающим
	ASprite.move(SpeedX * XDirection, SpeedY * YDirection);
}

void APlayerPawn::SetStance(EActionList Action)
{
	// ToDo Реализовать зедержку анимации
	switch (Action) {
	case EActionList::Move_Left:
		// Смена направления
		XDirection = -1;
		// Смена текущего кадра в зависимости от времени
		CurrPose = (CurrPose + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(64 * CurrPose, 64 * 2, 64, 64));
		break;

	case EActionList::Move_Right:
		XDirection = 1;
		// Смена текущего кадра в зависимости от времени
		CurrPose = (CurrPose + 1) % (ATexture.getSize().x / 64);
		ASprite.setTextureRect(sf::IntRect(64 * CurrPose, 64 * 1, 64, 64));
		break;

	case EActionList::Jump_Left:                 
		ASprite.setTextureRect(sf::IntRect(192, 0, 64, 64));
		break;

	case EActionList::Jump_Right:
		ASprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
		break;

	case EActionList::Idle_Left:
		ASprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
		CurrPose = 0;
		break;

	case EActionList::Idle_Right:
		ASprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		CurrPose = 0;
		break;
	}
	Clock.restart();
}

bool APlayerPawn::isAlive()
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
