/*
	����� ���������� �� ����������� ���� � �� �������� ���������� ������� ������.
	����� ���������� ��������� ������ � �������� ����. � ����� ��������� ���� ������ ������.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using FText = sf::Text;
using FString = sf::String;
using FFont = sf::Font;

const sf::Color Gray(90, 105, 136);


// ����� �������� ���� ����
class IMainMenu
{
private:
	int LvlChoose;
	bool isMenuClosed;
	FFont MenuFont;
	sf::Uint32 ScrWidth, ScrHeight;
	sf::Uint32 FrameRate;
	FFont Font;
	FText StartBtn, SettingBtn, EndBtn;
	sf::Texture LogoTexture;
	sf::Sprite Logo;

public:

	// ������������� ���������� ����. �������� ������ ����.
	IMainMenu(sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate);

	void Center(FText& ObjText);
	// ������� ��������� ������ ����
	int DrawCicle(sf::RenderWindow& window);

};

