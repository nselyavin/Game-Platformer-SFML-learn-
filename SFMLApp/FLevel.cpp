#include "FLevel.h"
#include "EEndStatus.h"

int FLevel::StartLevel(sf::RenderWindow& window, int ChoosenLvl)
{
	// ToDo сделать связь с парсером, который будет искать данные по выбранному уровню для построения уровня
	// Установка статусов игры
	bGameEnd = false;
	bGameWon = false;

	// Задача позиции игрока, пока вручную
	StartPos.x = window.getSize().x / 2;
	StartPos.y = window.getSize().y / 2;

	PlayerPawn.CreatePawn(StartPos.x, StartPos.y);

	int EndStatus = EEndStatus::GameError;
	EndStatus = DrawCicle(window);

	return EndStatus;
}


int FLevel::DrawCicle(sf::RenderWindow& window)
{
	// Здесь происходит главная отрисовка уровня, и считывание клавишь 
	while (!bGameEnd) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				bGameEnd = true;
				return EEndStatus::Exit;
			}
			
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					bGameEnd = true;
					return EEndStatus::Menu;
				}
			}
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			// Ходьба вправо
			PlayerPawn.SetStance(EActionList::Move_Right);
			PlayerPawn.MovePawn();
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			// Ходьба влево
			PlayerPawn.SetStance(EActionList::Move_Left);
			PlayerPawn.MovePawn();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
			// Прыжок в зависимости от направления
			if (PlayerPawn.GetXDirection() == -1)
				PlayerPawn.SetStance(EActionList::Jump_Left);
			else if (PlayerPawn.GetXDirection() == 1)
				PlayerPawn.SetStance(EActionList::Jump_Right);
			else
				return EEndStatus::GameError;
		}
		else {
			// Простаивание в зависимости от направления
			if (PlayerPawn.GetXDirection() == -1)
				PlayerPawn.SetStance(EActionList::Idle_Left);
			else if (PlayerPawn.GetXDirection() == 1)
				PlayerPawn.SetStance(EActionList::Idle_Right);
			else
				return EEndStatus::GameError;

		}

		window.clear(sf::Color::Yellow);
		PlayerPawn.DrawPawn(window);

		window.display();
	}
	return EEndStatus::Menu;
}

void FLevel::GameSummar(sf::RenderWindow& window)
{
	if (bGameWon)
		printf("Победа");
	else
		printf("Соси вторую жепу");
}

