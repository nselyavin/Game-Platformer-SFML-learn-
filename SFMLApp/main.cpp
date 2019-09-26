#include "IMainMenu.h"


int main()
{

	//TODO Реализовать чтение настроек из файла////////
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	ScrWidth = 800;
	ScrHeight = 600;
	FrameRate = 30;

	// Иницализации игрового пространства (окна, в котором происходит игра)
	// Установка соотношения сторон и частоты кадров
	sf::RenderWindow window(sf::VideoMode(ScrWidth, ScrHeight), "SFML works!");
	window.setFramerateLimit(FrameRate);

	// Инициализация класса меню.
	IMainMenu MainMenu(ScrWidth, ScrHeight, FrameRate);

	bool bGameEnd = false;
	int res = -1;
	// Родительский цикл игры, в нем происходит вызов основных этапов игры: меню, уровень и тд. — пока игра не закочнена
	while (!bGameEnd)
	{
		if (res == EEndStatus::Exit) {
			window.close();
			bGameEnd = true;
		}

		window.clear(); // ToDo на всякий случай потом убрать 
		res = MainMenu.DrawCicle(window);
		window.display();
	}

	return 0;
}