/*
	Файл принимающий настройки игры и раскидывающий их по переменным для дальнейшего использования
	Цикл запускает главное меню, а затем уровни
*/

#include "Headers\IMainMenu.h"
#include "Headers\FLevel.h"
#include "Headers\INIReader.h"
// #include <windows.h> Нужня для сокрытия консоли

sf::Int32 main()
{
	INIReader iniReader("\config.ini");
	// Код для сокрытия консоли, нужен для релизной сборки
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, iniReader.GetBoolean("other", "DebugConsole", 0));

	//TODO Реализовать чтение настроек из файла конфига
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	ScrWidth = iniReader.GetInteger("video", "ScreenWidth", 800);
	ScrHeight = iniReader.GetInteger("video", "ScreenHeight", 600);
	FrameRate = 32;
	// Режим окна
	UINT32 WindowStyle = sf::Style::Default;
	if (iniReader.GetBoolean("video", "FullScreen", false) == true)
		WindowStyle = sf::Style::Fullscreen;

	// Текущий уровень игры и всего уровней. ToDo реализовать изменения.
	sf::Uint32 CurrLvl = 0;
	sf::Uint32 TotalLvls = 1;

	// Иницализации игрового пространства (окна, в котором происходит игра)
	// Установка соотношения сторон и частоты кадров
	sf::RenderWindow window(sf::VideoMode(ScrWidth, ScrHeight, 64), "SFML works!", WindowStyle);
	window.setFramerateLimit(FrameRate);

	// Инициализация класса меню, уровня и загрузочного экрана.
	IMainMenu MainMenu;
	FLevel Level;
	sf::Texture LoadScrTex;
	sf::Sprite LoadScr;

	LoadScrTex.loadFromFile(SpritePath + "LoadScreen.jpg");
	LoadScr.setTexture(LoadScrTex);

	bool bGameEnd = false;
	sf::Int32 res = EEndStatus::Menu;
	// Родительский цикл игры, в нем происходит вызов основных этапов игры: меню, уровень и тд. — пока игра не закочнена
	while (!bGameEnd)
	{
		switch (res) {
		// Результирующие
		case EEndStatus::Menu:
			res = MainMenu.BeginMenu(window, ScrWidth, ScrHeight, FrameRate);
			break;

		case EEndStatus::StartGame:
			// Запускает нужный уровень.
			window.draw(LoadScr);
			window.display();
			CurrLvl = MainMenu.getSelectedLvl();
			res = Level.StartLevel(window, CurrLvl);
			break;

		case EEndStatus::ReturnGame:
			// Продолжать игру, не выкидывая в меню
			window.draw(LoadScr);
			window.display();
			if ((CurrLvl + 1) < TotalLvls) {
				CurrLvl++;
				res = Level.StartLevel(window, CurrLvl);
				break;
			}
			else {
				// ToDo Игра пройдена. Запуск титров.
				printf("The game is over");
			}

		// Завершающие
		case EEndStatus::Exit:
			// ToDo пофиксить краш при выходе из игры
			bGameEnd = true;
			window.close();
			break;

		///// Ошибки игры
		case EEndStatus::GameError:
			printf("Game was failed with error: %d", res);
			window.close();
			bGameEnd = true;
			system("pause");
			break;

		case EEndStatus::FileLoadFaled:
			printf("File load failed");
			window.close();
			bGameEnd = true;
			system("pause");
			break;

		default:
			printf("Game was crashed");
			window.close();
			bGameEnd = true;
			system("pause");
			break;
		}
		window.clear();
		window.display();
	}
	return 0;
}
