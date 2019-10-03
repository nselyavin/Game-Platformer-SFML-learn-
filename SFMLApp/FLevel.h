/*
	Этот класс собирает сцену из данных в файле.
	Здесь заложены функции для считывания действий игрока в игре. 
	Этот класс связан с классом пешки игрока и классом, и организует связанную работу между ними.
	По завершению уровня или выхода с уровня, должен возвращать соотвествующую ошибку
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "APlayerPawn.h"
#include "UWorld.h"

class ULevelStarter
{
private:
	// Объект игрока и мира
	APlayerPawn PlayerPawn;
	// Позиция спавна игрока
	sf::Vector2f StartPos;
	// Результаты\миссии игры. Проверка пройден или закончен ли уровен.
	bool bGameEnd, bGameWon;
public:
	// Иницализация класса, считывание файла по переданному названия. Задача спавна игрока и всех объектов
	// ToDo Поменять параметр представления уровня, на тот который будет читаться из файла. Или нет.
	int StartLevel(sf::RenderWindow& window, int ChoosenLvl);

	// Функция отрисовки игры
	void DrawLevel(sf::RenderWindow& window);

	// Показывается результаты урованя в зависимости от bGameWon
	void GameSummar(sf::RenderWindow& window);
	// Функци скроллинга мира 

};

