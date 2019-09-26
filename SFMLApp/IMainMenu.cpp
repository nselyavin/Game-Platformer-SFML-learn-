#include "IMainMenu.h"
#include <iostream>;

IMainMenu::IMainMenu(sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate)
{
	this->ScrWidth = ScrWidth;
	this->ScrHeight = ScrHeight;
	this->FrameRate = FrameRate;
	bMenuClosed = false;

	// Задаем тексутры, рект и позицию для логотипа
	LogoTexture.loadFromFile("..\\Resource\\Logo.png");

	Logo.setTexture(LogoTexture);
	sf::FloatRect LogoRect = Logo.getLocalBounds();
	Logo.setOrigin(LogoRect.left + LogoRect.width / 2,
						LogoRect.top + LogoRect.height / 2);
	Logo.setPosition(ScrWidth / 2, 130);

	// Задний фон игры
	BackMenuText.loadFromFile("..\\Resource\\MenuBack.png");
	BackMenu.setTexture(BackMenuText);

	// ToDo реализовать ошибку при не подключении шрифта
	Font.loadFromFile("..\\Resource\\MenuFont.ttf");

	StartBtn.setString("Start Game");
	StartBtn.setFont(Font);
	StartBtn.setCharacterSize(45);

	SettingBtn.setString("Setting");
	SettingBtn.setFont(Font);
	SettingBtn.setCharacterSize(45);

	EndBtn.setString("End Game");
	EndBtn.setFont(Font);
	EndBtn.setCharacterSize(45);
}

void IMainMenu::Center(FText &ObjText)
{
	sf::FloatRect TextRect = ObjText.getLocalBounds();
	ObjText.setOrigin(TextRect.left + TextRect.width / 2,
						TextRect.top + TextRect.height / 2);

	ObjText.setPosition(ScrWidth / 2, ScrHeight / 2);

}

int IMainMenu::DrawCicle(sf::RenderWindow& window)
{

	sf::FloatRect StartBtnRect = StartBtn.getLocalBounds();
	sf::FloatRect SettingBtnRect= SettingBtn.getLocalBounds();
	sf::FloatRect EndBtnRect = EndBtn.getLocalBounds();

	Center(StartBtn);
	StartBtn.setPosition(ScrWidth / 2, 260);
	Center(SettingBtn);
	SettingBtn.setPosition(ScrWidth / 2, 340);
	Center(EndBtn);
	EndBtn.setPosition(ScrWidth / 2, 420);

	// toDo Нужно реализовать enum ошибок.
	// Здесь можно ретюрнить все ошибки через код, следовательно делать проверки.  
	while (!bMenuClosed) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				bMenuClosed = true;
				return EEndStatus::Exit;
			}
			
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					bMenuClosed = true;
					return EEndStatus::Exit;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left) {
					//std::cout << "Left Mouse coord: " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
					if (event.mouseButton.x > EndBtn.getGlobalBounds().left &&	event.mouseButton.x < (EndBtn.getGlobalBounds().left + EndBtnRect.width)) {
						if (event.mouseButton.y > EndBtn.getGlobalBounds().top && event.mouseButton.y < (EndBtn.getGlobalBounds().top + EndBtnRect.height)) {
							bMenuClosed = true;
							return EEndStatus::Exit;
						}
					}
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				if (event.mouseMove.x > EndBtn.getGlobalBounds().left && event.mouseMove.x < (EndBtn.getGlobalBounds().left + EndBtnRect.width)) {
					if (event.mouseMove.y > EndBtn.getGlobalBounds().top && event.mouseMove.y < (EndBtn.getGlobalBounds().top + EndBtnRect.height)) {
						EndBtn.setFillColor(Reds);
					}
					else
						EndBtn.setFillColor(sf::Color::White);
				}
			}
		}

		window.clear();

		window.draw(BackMenu);
		window.draw(Logo);
		window.draw(StartBtn);
		window.draw(SettingBtn);
		window.draw(EndBtn);
		
		window.display();
	}
	return EEndStatus::NextLevel;
}
