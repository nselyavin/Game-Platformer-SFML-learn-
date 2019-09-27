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
	float Speed;
	// Направление персонажа по X, 0 - влево, 1 - вправо
	sf::Int8 XDirection = 1;
	// Текущая поза игрока при воспроизведении анимации
	int CurrPose;
	

public:
	// Инициализация массива по позиции из игрока из класса мира.
	APlayerPawn();

	// Инициализация пешки игрока 
	void BeginPawn(sf::RenderWindow &window, float x, float y);

	// Цикл отображения пешки
	void DrawPawn(sf::RenderWindow &window);

	// Метод смены спрайта в зависимости от направления
	void SetPose(EActionList Action);

	// Спрашивает жив ли игрок
	bool isAlive();

	// Возвращает ссылку объект спрайта игрока
	const sf::Sprite& GetSprite();

	// Возвращает ссылку объект текстуры игрока
	const sf::Texture& GetTexture();

	// Возвращает позицию игрока
	const sf::Vector2f& GetPos();

	// Вовзращает жизни игрока
	int GetHealth();

	// Возвращает скорость игрока
	float GetSpeed();
};

