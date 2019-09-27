/*
	Файл принимающий настройки игры и раскидывающий их по переменным для дальнейшего использования
	Цикл запускает главное меню, а затем уровни
*/

#include "IMainMenu.h"
#include "APlayerPawn.h"


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
	IMainMenu MainMenu;

	bool bGameEnd = false;
	int res = EEndStatus::Begin;
	// Родительский цикл игры, в нем происходит вызов основных этапов игры: меню, уровень и тд. — пока игра не закочнена
	while (!bGameEnd)
	{
		switch (res) {
		case EEndStatus::Exit:
			window.close();
			bGameEnd = true;
			break;

		case EEndStatus::Begin:
			res = MainMenu.BeginMenu(window, ScrWidth, ScrHeight, FrameRate);
			break;

		case EEndStatus::StartGame:
			// ToDo Реализовать систему выбора уровня
			printf("Sosi jepu");
			res = EEndStatus::Begin;
			break;

		case EEndStatus::GameError:
			printf("Game was failed with erroe: %d", res);
			window.close();
			system("pause");
			break;

		default:
			printf("Game was crashed");
			window.close();
			system("pause");
			break;
		}
		window.clear();
		window.display();
	}

	return 0;
}