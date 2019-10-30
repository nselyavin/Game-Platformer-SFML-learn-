/*
	Класс отвечающий за отображение меню и за вовзврат выбранного игроком уровня.
	Здесь происходит отрисовка кнопок и логотипа игры. А также отрисовка меню выбора уровня.
*/

#pragma once

#include "GameConst.h"

using FText = sf::Text;
using FString = sf::String;
using FFont = sf::Font;

const sf::Color Gray(90, 105, 136);

// Класс главного меню игры
class IMainMenu
{
private:
	// Результат активации кнопок
	sf::Int32 MenuStatus;
	// Вабранный уровень
	sf::Int32 SelectedLvl;
	// Текущий тайл задней анимации
	sf::Int32 CurrBackSlide;
	bool bMenuClosed;
	// Характеристики window
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	// Последняя позиция мыши, чтобы проверить сдвигалась ли она
	sf::Vector2f LastMousePos;
	// Шрифт кнопок
	FFont Font;
	// Спрайты кнопок в виде текста
	FText StartBtn, SettingBtn, EndBtn;
	// Текстуры и спрайты логотипа и заднего фона меню
	sf::Texture LogoTexture, BackMenuText;
	sf::Sprite Logo, BackMenu;

public:
	IMainMenu();

	// Создает меню, находит файлы игры, создает объекты
	sf::Int32 BeginMenu(sf::RenderWindow& window, sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate);
	
	// Центрирование текста на экране
	void Center(FText& ObjText);

	// Функция активации кнопки 
	sf::Int32 BtnActivate(sf::Int32 CurrBtn);

	//Функция изменения цвета кнопки 
	void BtnFill(sf::Int32 CurrBtn);

	// Рисует текстовые пункты меню
	sf::Int32 DrawCicle(sf::RenderWindow& window);

	// Вовзращает последний выбранный уровень
	const sf::Int32 getSelectedLvl();
};