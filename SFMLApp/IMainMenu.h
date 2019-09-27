/*
	Класс отвечающий за отображение меню и за вовзврат выбранного игроком уровня.
	Здесь происходит отрисовка кнопок и логотипа игры. А также отрисовка меню выбора уровня.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EEndStatus.h"

using FText = sf::Text;
using FString = sf::String;
using FFont = sf::Font;

const sf::Color Gray(90, 105, 136);
const sf::Color Reds = sf::Color::Red;

// Класс главного меню игры
class IMainMenu
{
private:
	int LvlChoose;
	bool bMenuClosed;
	FFont MenuFont;
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	FFont Font;
	FText StartBtn, SettingBtn, EndBtn;
	sf::Texture LogoTexture, BackMenuText;
	sf::Sprite Logo, BackMenu;

public:
	int BeginMenu(sf::RenderWindow& window, sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate);

	void Center(FText& ObjText);
	// Создает текстовые пункты меню
	int DrawCicle(sf::RenderWindow& window);

};

