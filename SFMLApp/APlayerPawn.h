/*
	Класс игрока, который задает характеристики пешки и загружает текстуру для спрайта пешки
	ВНИМАНИЕ: Каждый тайл текстуры должен быть размером 64х64 пикселя, много тайловая текстура с каждой стороны должна быть кратна 64.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


enum EActionList
{
	Idle,
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
	bool bAlive;
	int Health;
	float Speed;
	// Текущая позиция игрока по [0] = Х и [1] = У
	float pos[2];
	// Текущая поза игрока по [0] = Row и [1] = Line
	int CurrPose[2];

public:
	// Инициализация массива по позиции из игрока из класса мира.
	APlayerPawn(float x, float y);

	// Цикл отображения пешки
	int PawnDrawCicle(sf::RenderWindow &window);

	// Метод смены спрайта в зависимости от направления
	void SetPose(EActionList Action);

	// Методы геторы всех параметров
};

