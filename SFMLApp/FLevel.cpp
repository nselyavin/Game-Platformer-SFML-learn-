#include "FLevel.h"
#include <windows.h>

int FLevel::StartLevel(sf::RenderWindow& window, sf::Uint32 ChoosenLvl)
{
	Camera.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	// ToDo сделать связь с парсером, который будет искать данные по выбранному уровню для построения уровня


	// Установка статусов игры
	bGameEnd = false;
	bGameWon = false;

	// Инициализации пешки и мира
	PlayerPawn.CreatePawn(StartPos.x, StartPos.y);
	World.CreateWorld(1);

	// Стартовая позиция игрока
	PlayerPawn.setPosition(World.getStartPos());

	Sleep(1000);

	int EndStatus = EEndStatus::GameError;
	EndStatus = DrawCicle(window);

	return EndStatus;
}


int FLevel::DrawCicle(sf::RenderWindow& window)
{
	sf::Clock clock;
	float LastTime = 0;
	int delay = 0;

	// Здесь происходит главная отрисовка уровня, и считывание действий игрока
	while (!bGameEnd) {
		
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		LastTime = currentTime;

		if (delay < 1000) {
			printf("fps: %d", (int)fps);
			delay = 0;
		}
		else {
			delay++;
		}
		

		// Проверка событий в игре
		sf::Event event;
		while (window.pollEvent(event)) {
			// Выход из игры
			if (event.type == sf::Event::Closed) {
				bGameEnd = true;
				return EEndStatus::Exit;
			}
			
			// Выход в меню
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					bGameEnd = true;
					return EEndStatus::Menu;
				}
			}
		}

		// Проверяет зажата ли клавиша
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
		// Изменение позиции камеры 
		setView(PlayerPawn.GetPos());

		// Очистка экрана для отрисовки
		window.setView(Camera);
		window.clear();

		// Основное тело отрисовки
		World.DrawWorld(window);
		PlayerPawn.DrawPawn(window);
		
		// Обновление экрана. Включает в себя задержку, зависящей от FrameRate
		window.display();
	}
	return EEndStatus::Menu;
}

sf::View FLevel::setView(sf::Vector2f Pos) {
	Camera.setCenter(Pos.x + 100, Pos.y);
	return Camera;
}

void FLevel::GameSummar(sf::RenderWindow& window)
{
	if (bGameWon)
		printf("Победа");
	else
		printf("Соси вторую жепу");
}

