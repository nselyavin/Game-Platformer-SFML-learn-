/*
	Класс игрока, который задает характеристики пешки и загружает текстуру для спрайта пешки
	ВНИМАНИЕ: Каждый тайл текстуры должен быть размером 64х64 пикселя, много тайловая текстура с каждой стороны должна быть кратна 64.
*/
#pragma once

#include "GameConst.h"
#include <cmath>

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
	Down_Right,
	Idle_Vertical // ToDo Убрать после реализации прыжка 
};

struct FMoveDeny {
	bool Top, Down, Left, Right;
};

class APlayerPawn
{
private:
	sf::Texture ATexture;
	sf::Sprite ASprite; 
	sf::FloatRect PawnRect;
	// Нужны для плавной смены поз
	FClock Clock;
	// Задержка для смены кадров
	sf::Int32 delay;
	// Показывает на земле ли персонаж
	bool bOnEarth;
	// Жизни персонажа
	sf::Int32 Health;
	// Масса персонажа
	float Mass;
	float Gravity;
	sf::Vector2f Speed;
	EDirection XDirection;
	EDirection YDirection;
	// Текущая поза игрока при воспроизведении анимации
	sf::Int32 CurrPoseFrame;
	// Текущее действие
	EActionList Action;

public:
	APlayerPawn();

	// Инициализация пешки игрока 
	sf::Int32 CreatePawn(float x, float y);

	// Цикл отображения пешки
	void DrawPawn(sf::RenderWindow &window);

	// Влияние действий игрока на скорость персонажа
	void ChangeSelfSpeed(EActionList Action);

	// Двигает пешку влево
	void MoveLeft();

	// Двигает пешку вправо
	void MoveRight();
	
	// Двигает пешку вправо
	void Jump();

	// Модификаторы скорости. Следует вызывать всегда
	void MoveModificators();

	// Функция движения персонажа
	void AcceptMove();

	// Задает текущую позицию. Влияние внешних сил
	void setPosition(sf::Vector2f Pos);

	// Задает текущую позицию. Влияние внешних сил
	void setSpeed(sf::Vector2f Speed);

	// Устанавливает жизни пешки
	void setHealth(sf::Int32 Health);

	// Спрашивает жив ли игрок
	bool isAlive();

	// Проверяет на земел ли пешка
	bool& pOnEarthStatus();

	// Возвращает ссылку объект спрайта игрока
	const sf::Sprite GetSprite();

	// Возвращает ссылку объект текстуры игрока
	const sf::Texture GetTexture();

	// Возвращает рект спарйта игрока
	const sf::FloatRect GetPawnRect();

	// Возвращает позицию игрока
	const sf::Vector2f GetPos();

	// Возвращает скорость игрока
	const sf::Vector2f GetSpeed();

	// Вовзращает жизни игрока
	const sf::Int32 GetHealth();

	// Возвращает направление игрока
	const EDirection GetXDirection();

	// Возвращает направление игрока
	const EDirection GetYDirection();

protected:
	// Метод смены спрайта в зависимости от направления
	void ChangePose();
};

