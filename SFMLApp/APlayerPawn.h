/*
	Класс игрока, который задает характеристики пешки и загружает текстуру для спрайта пешки
	ВНИМАНИЕ: Каждый тайл текстуры должен быть размером 64х64 пикселя, много тайловая текстура с каждой стороны должна быть кратна 64.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "GameConst.h"

using FClock = sf::Clock;

enum EActionList
{
	Idle_Left,
	Idle_Right,
	Jump_Left,
	Jump_Right,
	Move_Left,
	Move_Right,
	Down_Left,
	Down_Right
};

struct FMoveDeny {
	bool Top, Down, Left, Right;
};

class APlayerPawn
{
private:
	FMoveDeny MoveDeny = { false, false, false, false };
	sf::Texture ATexture;
	sf::Sprite ASprite; 
	sf::FloatRect PawnRect;
	// Нужны для плавной смены поз
	FClock Clock;
	// Задержка для смены кадров
	int delay;
	// Статус жив ли персонаж
	bool bAlive;
	// Жизни персонажа
	int Health;
	// Масса персонажа
	float Mass;
	float SpeedX, SpeedY, Gravity;
	// Направление персонажа по X, -1 - влево, 1 - вправо
	sf::Int8 XDirection = 1;
	// Направление персонажа по Y, -1 - вверх, 1 - вниз
	sf::Int8 YDirection = -1;
	// Текущая поза игрока при воспроизведении анимации
	int CurrPose;

public:
	APlayerPawn();

	// Инициализация пешки игрока 
	int CreatePawn(float x, float y);

	// Цикл отображения пешки
	void DrawPawn(sf::RenderWindow &window);

	// Метод смены спрайта в зависимости от направления
	void SetStance(EActionList Action);

	// 
	void ChangeSelfSpeed(EActionList Action);

	// Функция движения персонажа
	void MovePawn();

	// Задает текущую позицию. Влияние внешних сил
	void setPosition(sf::Vector2f Pos);

	// Спрашивает жив ли игрок
	const bool isAlive();

	// Возвращает ссылку объект спрайта игрока
	const sf::Sprite& GetSprite();

	// Возвращает ссылку объект текстуры игрока
	const sf::Texture& GetTexture();

	// Возвращает рект спарйта игрока
	const sf::FloatRect& GetPawnRect();

	// Возвращает позицию игрока
	const sf::Vector2f& GetPos();

	// Возвращает скорость игрока
	const sf::Vector2f GetSpeed();

	// Вовзращает жизни игрока
	const int GetHealth();

	// Возвращает направление игрока
	const sf::Int8 GetXDirection();

	FMoveDeny& getMoveDeny();
};

