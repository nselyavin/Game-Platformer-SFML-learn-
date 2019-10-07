/*
	Класс отвечающий за отображение меню и за вовзврат выбранного игроком уровня.
	Здесь происходит отрисовка кнопок и логотипа игры. А также отрисовка меню выбора уровня.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameConst.h"

using FText = sf::Text;
using FString = sf::String;
using FFont = sf::Font;

const sf::Color Gray(90, 105, 136);

// Класс главного меню игры
class IMainMenu
{
private:
	int SelectedLvl = 0;
	int CurrLvl = 0;
	bool bMenuClosed;
	FFont MenuFont;
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	FFont Font;
	FText StartBtn, SettingBtn, EndBtn;
	sf::Texture LogoTexture, BackMenuText;
	sf::Sprite Logo, BackMenu;

public:
	// Создает меню, находит файлы игры, создает объекты
	int BeginMenu(sf::RenderWindow& window, sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate);
	
	// Центрирование текста на экране
	void Center(FText& ObjText);

	// Рисует текстовые пункты меню
	int DrawCicle(sf::RenderWindow& window);

	// Вовзращает последний выбранный уровень
	const int getSelectedLvl();
};

