#include "IMainMenu.h"
#include <iostream>;

IMainMenu::IMainMenu(sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate)
{
	this->ScrWidth = ScrWidth;
	this->ScrHeight = ScrHeight;
	this->FrameRate = FrameRate;
	isMenuClosed = false;
	Font.loadFromFile("..\\Resourse\\MenuFont.ttf");

	Button.setString("");
	Button.setFont(Font);
	Button.setCharacterSize(70);
}

void IMainMenu::DrawText(sf::RenderWindow& window, const FString OutText, int height)
{
	sf::FloatRect ButtonRect = Button.getLocalBounds();
	Button.setOrigin(ButtonRect.left + ButtonRect.width / 2,
					ButtonRect.top + ButtonRect.height / 2);


	// ToDo додвигать текста в центр, или поменять их на спрайты
	Button.setString(OutText);
	Button.setPosition(ScrWidth / 2, height);
	window.draw(Button);
}

int IMainMenu::DrawCicle(sf::RenderWindow& window)
{
	FFont Font;
	Font.loadFromFile("..\\Resourse\\MenuFont.ttf");


	while (!isMenuClosed) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				isMenuClosed = true;
				return 1;
			}
		}

		window.clear(Gray);
		
		DrawText(window, StartStr, 150);
		DrawText(window, SettingStr, 250);
		DrawText(window, EndStr, 350);
		
		window.display();
	}
	return 0;
}
