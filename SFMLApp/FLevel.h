/*
	Этот класс собирает сцену из данных в файле.
	Здесь заложены функции для считывания действий игрока в игре. 
	Этот класс связан с классом пешки игрока и классом, и организует связанную работу между ними.
	По завершению уровня или выхода с уровня, должен возвращать соотвествующую ошибку
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "XMLtoMap.h"
#include "APlayerPawn.h"
#include "UWorld.h"
#include "GameConst.h"

class FLevel
{
private:
	sf::View Camera;
	// Объект игрока и мира
	APlayerPawn PlayerPawn;
	UWorld World;
	// Позиция спавна игрока
	sf::Vector2f StartPos;
	float LocalTime;
	// Результаты\миссии игры. Проверка пройден или закончен ли уровен.
	bool bGameEnd, bGameWon;
public:
	FLevel();

	// Иницализация класса, считывание файла по переданному названия. Задача спавна игрока и всех объектов
	// ToDo Поменять параметр представления уровня, на тот который будет читаться из файла. Если понадобится.
	int StartLevel(sf::RenderWindow& window, sf::Uint32 SelectedLvl);


	// Функция отрисовки игры
	int DrawCicle(sf::RenderWindow& window);

	// Показывается результаты урованя в зависимости от bGameWon
	void GameSummar(sf::RenderWindow& window);
	
	// Функция следования камеры за игроком по позиции игрока
	sf::View setView(sf::Vector2f Pos);


};

