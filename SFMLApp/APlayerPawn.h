/*
	Класс игрока, который задает характеристики пешки и загружает текстуру для спрайта пешки
	ВНИМАНИЕ: Каждый тайл текстуры должен быть размером 64х64 пикселя, много тайловая текстура с каждой стороны должна быть кратна 64.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using FClock = sf::Clock;

enum EActionList
{
	Idle_Left,
	Idle_Right,
	Jump_Left,
	Jump_Right,
	Move_Left,
	Move_Right
};

class APlayerPawn
{
private:
	sf::Texture ATexture;
	sf::Sprite ASprite; 
	// Нужны для плавной смены поз
	FClock Clock;
	// Задержка для смены кадров
	int delay;
	bool bAlive;
	int Health;
	float SpeedX, SpeedY;
	// Направление персонажа по X, -1 - влево, 1 - вправо
	sf::Int8 XDirection = 1;
	// Направление персонажа по Y, -1 - вверх, 1 - вниз
	sf::Int8 YDirection = -1;
	// Текущая поза игрока при воспроизведении анимации
	int CurrPose;
	

public:
	// Инициализация пешки игрока 
	int CreatePawn(float x, float y);

	// Цикл отображения пешки
	void DrawPawn(sf::RenderWindow &window);

	// Метод смены спрайта в зависимости от направления
	void SetStance(EActionList Action);

	// Спрашивает жив ли игрок
	bool isAlive();

	// Функция движения персонажа
	void MovePawn();

	// Возвращает ссылку объект спрайта игрока
	const sf::Sprite& GetSprite();

	// Возвращает ссылку объект текстуры игрока
	const sf::Texture& GetTexture();

	// Возвращает позицию игрока
	const sf::Vector2f& GetPos();

	// Возвращает скорость игрока
	const sf::Vector2f GetSpeed();

	// Вовзращает жизни игрока
	const int GetHealth();

	// Возвращает направление игрока
	const sf::Int8 GetXDirection();
};

