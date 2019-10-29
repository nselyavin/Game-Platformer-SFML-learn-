/*
	���� ����������� ��������� ���� � ������������� �� �� ���������� ��� ����������� �������������
	���� ��������� ������� ����, � ����� ������
*/

#include "Headers\IMainMenu.h"
#include "Headers\FLevel.h"
// #include <windows.h> ����� ��� �������� �������

sf::Int32 main()
{
	/* // ��� ��� �������� �������, ����� ��� �������� ������
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 1);
	*/

	//TODO ����������� ������ �������� �� ����� �������
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	ScrWidth = 800;
	ScrHeight = 600;
	FrameRate = 64;

	// ������� ������� ���� � ����� �������. ToDo ����������� ���������.
	sf::Uint32 CurrLvl = 0;
	sf::Uint32 TotalLvls = 1;

	// ������������ �������� ������������ (����, � ������� ���������� ����)
	// ��������� ����������� ������ � ������� ������
	sf::RenderWindow window(sf::VideoMode(ScrWidth, ScrHeight, 64), "SFML works!");
	window.setFramerateLimit(FrameRate);

	// ������������� ������ ����, ������ � ������������ ������.
	IMainMenu MainMenu;
	FLevel Level;
	sf::Texture LoadScrTex;
	sf::Sprite LoadScr;

	LoadScrTex.loadFromFile(SpritePath + "LoadScreen.jpg");
	LoadScr.setTexture(LoadScrTex);

	bool bGameEnd = false;
	sf::Int32 res = EEndStatus::Menu;
	// ������������ ���� ����, � ��� ���������� ����� �������� ������ ����: ����, ������� � ��. � ���� ���� �� ���������
	while (!bGameEnd)
	{
		switch (res) {
		// ��������������
		case EEndStatus::Menu:
			res = MainMenu.BeginMenu(window, ScrWidth, ScrHeight, FrameRate);
			break;

		case EEndStatus::StartGame:
			// ��������� ������ �������.
			window.draw(LoadScr);
			window.display();
			CurrLvl = MainMenu.getSelectedLvl();
			res = Level.StartLevel(window, CurrLvl);
			break;

		case EEndStatus::ReturnGame:
			// ���������� ����, �� ��������� � ����
			window.draw(LoadScr);
			window.display();
			if ((CurrLvl + 1) < TotalLvls) {
				CurrLvl++;
				res = Level.StartLevel(window, CurrLvl);
				break;
			}
			else {
				// ToDo ���� ��������. ������ ������.
				printf("The game is over");
			}

		// �����������
		case EEndStatus::Exit:
			// ToDo ��������� ���� ��� ������ �� ����
			bGameEnd = true;
			window.close();
			break;

		///// ������ ����
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
