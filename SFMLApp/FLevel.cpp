#include "FLevel.h"
#include <windows.h>

FLevel::FLevel()
{
	LocalTime = 0;
	bGameEnd = true;
	bGameWon = false;
}

int FLevel::StartLevel(sf::RenderWindow& window, sf::Uint32 ChoosenLvl)
{
	Camera.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	// ToDo сделать связь с парсером, который будет искать данные по выбранному уровню для построения уровня


	// Установка статусов игры
	bGameEnd = false;
	bGameWon = false;

	// Инициализации пешки и мира
	PlayerPawn.CreatePawn(StartPos.x, StartPos.y);
	World.CreateWorld(ChoosenLvl);

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

		/* // Количество кадров в секунду
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
		*/
		
		

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
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
			// Прыжок в зависимости от направления
			PlayerPawn.setPosition(sf::Vector2f(PlayerPawn.GetPos().x, PlayerPawn.GetPos().y + 10));

		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
			// Прыжок в зависимости от направления
			PlayerPawn.setPosition(sf::Vector2f(PlayerPawn.GetPos().x, PlayerPawn.GetPos().y - 10));
		}
		/*
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
			// Прыжок в зависимости от направления
			if (PlayerPawn.GetXDirection() == -1)
				PlayerPawn.ChangeSelfSpeed(EActionList::Jump_Left);
			else if (PlayerPawn.GetXDirection() == 1)
				PlayerPawn.ChangeSelfSpeed(EActionList::Jump_Right);
			else
				return EEndStatus::GameError;
		}
		*/

		// Проверяет зажата ли клавиша
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			// Ходьба вправо
			PlayerPawn.ChangeSelfSpeed(EActionList::Move_Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			// Ходьба влево
			PlayerPawn.ChangeSelfSpeed(EActionList::Move_Left);
		}
		else {
			// Простаивание в зависимости от направления
			if (PlayerPawn.GetXDirection() == -1)
				PlayerPawn.ChangeSelfSpeed(EActionList::Idle_Left);
			else if (PlayerPawn.GetXDirection() == 1)
				PlayerPawn.ChangeSelfSpeed(EActionList::Idle_Right);
			else
				return EEndStatus::GameError;
		}

		// Общее движение пешки
		PlayerPawn.MovePawn();

		// Проверка пересекает ли персонаж коллизию
		World.getCollisDirect(PlayerPawn.GetPawnRect(), PlayerPawn.getMoveDeny().Top, PlayerPawn.getMoveDeny().Down, PlayerPawn.getMoveDeny().Left, PlayerPawn.getMoveDeny().Right);

		// ToDo Корректировка позиции пешки.

		// Изменение позиции камеры 
		setView(PlayerPawn.GetPos());

		/// Часть отрисовки \\\
		// Очистка экрана для отрисовки
		window.setView(Camera);
		window.clear();

		// Основное тело отрисовки
		World.DrawWorld(window, Camera.getCenter(),Camera.getSize());
		PlayerPawn.DrawPawn(window);

		// Обновление экрана. Включает в себя задержку, зависящей от FrameRate
		window.display();
	}
	return EEndStatus::Menu;
}

sf::View FLevel::setView(sf::Vector2f Pos) {
	// ToDo когда в игре будет больше 2 пешек, доабвить динамичное изменение размеры камеры, по мере отдаления пешек друг от друга.
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

