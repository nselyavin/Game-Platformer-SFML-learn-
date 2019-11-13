#include "Headers\IMainMenu.h"
#include <iostream>;

IMainMenu::IMainMenu()
{
	SelectedLvl = 0;
	CurrBackSlide = 0;
	bMenuClosed = 0;

}

sf::Int32 IMainMenu::BeginMenu(sf::RenderWindow &window, sf::Uint32 ScrWidth, sf::Uint32 ScrHeight, sf::Uint32 FrameRate)
{
	// Сбрасывает позицию камеры до нулевой, чтобы меню не съезжало
	sf::View Camera;
	Camera.reset(sf::FloatRect(0, 0, ScrWidth, ScrHeight));
	window.setView(Camera);

	// Сохранение параметров экрана
	this->ScrWidth = ScrWidth;
	this->ScrHeight = ScrHeight;
	this->FrameRate = FrameRate;

	// Инициализация последней позиции мыши
	LastMousePos.x = 0;
	LastMousePos.y = 0;

	MenuStatus = EEndStatus::Menu;

	// Статус закрытия меню
	bMenuClosed = false;

	// Задаем тексутры, рект и позицию для логотипа
	if (!LogoTexture.loadFromFile(SpritePath + "Logo.png")) {
		printf("Menu:\nLogo img: ");
		return EEndStatus::FileLoadFaled;
	}

	Logo.setTexture(LogoTexture);
	sf::FloatRect LogoRect = Logo.getLocalBounds();
	Logo.setOrigin(LogoRect.left + LogoRect.width / 2,
		LogoRect.top + LogoRect.height / 2);
	Logo.setPosition(ScrWidth / 2, ScrHeight/2 - 230);

	// Задний фон игры
	if (!BackMenuText.loadFromFile(SpritePath + "MenuBack.png")) {
		printf("Menu:\nBackground img: ");
		return EEndStatus::FileLoadFaled;
	}
	BackMenu.setTexture(BackMenuText);

	if (!Font.loadFromFile(FontPath + MenuFont)) {
		printf("Menu:\nFont: ");
		return EEndStatus::FileLoadFaled;
	}

	// Задает текст, шрифт, размер кнопок меню
	StartBtn.setString("Start Game");
	StartBtn.setFont(Font);
	StartBtn.setCharacterSize(45);

	SettingBtn.setString("Setting");
	SettingBtn.setFont(Font);
	SettingBtn.setCharacterSize(45);

	EndBtn.setString("End Game");
	EndBtn.setFont(Font);
	EndBtn.setCharacterSize(45);





	sf::Int32 EndStatus = EEndStatus::GameError;
	EndStatus = DrawCicle(window);

	return EndStatus;
}

void IMainMenu::Center(FText &ObjText)
{
	sf::FloatRect TextRect = ObjText.getLocalBounds();
	ObjText.setOrigin(TextRect.left + TextRect.width / 2,
						TextRect.top + TextRect.height / 2);

	ObjText.setPosition(ScrWidth / 2, ScrHeight / 2);

}

sf::Int32 IMainMenu::BtnActivate(sf::Int32 CurrBtn)
{
	// Активирует действие в зависимости от кнопки 
	switch (CurrBtn) {
	case(0):
		SelectedLvl = 1;
		bMenuClosed = true;
		return EEndStatus::StartGame; 
		break;
	case(1):
		// Вызывается цикл окна настроек (рекурсия)
		printf("Nothing");
		return EEndStatus::Menu;
		break;
	case(2):
		bMenuClosed = true;
		return EEndStatus::Exit;
		break;
	default:
		return EEndStatus::Menu;
	}
}

void IMainMenu::BtnFill(sf::Int32 CurrBtn)
{
	// Сбросс цвета выбранной кнопки
	StartBtn.setFillColor(sf::Color::Color(255, 255, 255));
	SettingBtn.setFillColor(sf::Color::Color(255, 255, 255));
	EndBtn.setFillColor(sf::Color::Color(255, 255, 255));

	// Покрасс текущей кнопки
	switch (CurrBtn) {
	case(0):
		StartBtn.setFillColor(sf::Color::Color(0, 255, 255));
		break;
	case(1):
		SettingBtn.setFillColor(sf::Color::Color(0, 255, 255));
		break;
	case(2):
		EndBtn.setFillColor(sf::Color::Color(0, 255, 255));
		break;
	}
}

sf::Int32 IMainMenu::DrawCicle(sf::RenderWindow& window)
{
	// Текущий выбранный пункт меню
	sf::Int32 CurrBtn = -1;

	// Получение ректов кнопок
	sf::FloatRect StartBtnRect = StartBtn.getLocalBounds();
	sf::FloatRect SettingBtnRect = SettingBtn.getLocalBounds();
	sf::FloatRect EndBtnRect = EndBtn.getLocalBounds();

	// Центрирование кнопок по середине экрана
	Center(StartBtn);
	StartBtn.setPosition(ScrWidth / 2, ScrHeight/2 - 100);
	Center(SettingBtn);
	SettingBtn.setPosition(ScrWidth / 2, ScrHeight/2);
	Center(EndBtn);
	EndBtn.setPosition(ScrWidth / 2, ScrHeight/2 + 100);

	// Здесь можно ретюрнить все ошибки через код, следовательно делать проверки.  
	while (!bMenuClosed) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				bMenuClosed = true;
				return EEndStatus::Exit;
			}
			
			// Проверка нажатий клавиш
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					bMenuClosed = true;
					return EEndStatus::Exit;
				}

				// Изменять выбранную кнопку если нажимаются стрелки
				if (event.key.code == sf::Keyboard::Down) {
					if (CurrBtn < 0)
						CurrBtn = 0;

					CurrBtn = (CurrBtn + 1) % 3;

					// Вызов функции покраски кнопок в зависимости от текущей выбранной кнопки
					BtnFill(CurrBtn);
				}
				else if (event.key.code == sf::Keyboard::Up) {
					CurrBtn = CurrBtn - 1;

					if (CurrBtn < 0)
						CurrBtn = 2;

					// Вызов функции покраски кнопок в зависимости от текущей выбранной кнопки
					BtnFill(CurrBtn);
				}

				// Активировать текущую кнопку 
				if (event.key.code == sf::Keyboard::Enter) {
					MenuStatus = BtnActivate(CurrBtn);
				}
			}
			
			// Активировать текущую кнопку 
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left) {
					MenuStatus = BtnActivate(CurrBtn);
				}
			}
			
			// Проверка для покраски кнопок
			if (event.type == sf::Event::MouseMoved) {
				if (LastMousePos.x != event.mouseMove.x && LastMousePos.y != event.mouseMove.y) {
					CurrBtn = -1;

					// Координаты кнопки старта.
					if (event.mouseMove.x > StartBtn.getGlobalBounds().left&& event.mouseMove.x < (StartBtn.getGlobalBounds().left + StartBtnRect.width)) {
						if (event.mouseMove.y > StartBtn.getGlobalBounds().top&& event.mouseMove.y < (StartBtn.getGlobalBounds().top + StartBtnRect.height)) {
							CurrBtn = 0;	
						}
					}

					// Координаты кнопки настроек.
					if (event.mouseMove.x > SettingBtn.getGlobalBounds().left&& event.mouseMove.x < (SettingBtn.getGlobalBounds().left + SettingBtnRect.width)) {
						if (event.mouseMove.y > SettingBtn.getGlobalBounds().top&& event.mouseMove.y < (SettingBtn.getGlobalBounds().top + SettingBtnRect.height)) {
							CurrBtn = 1;
						}
					}

					// Координаты кнопки выхода.
					if (event.mouseMove.x > EndBtn.getGlobalBounds().left&& event.mouseMove.x < (EndBtn.getGlobalBounds().left + EndBtnRect.width)) {
						if (event.mouseMove.y > EndBtn.getGlobalBounds().top&& event.mouseMove.y < (EndBtn.getGlobalBounds().top + EndBtnRect.height)) {
							CurrBtn = 2;
						}

					}

					// Запомоминание последней позиции мыши 
					LastMousePos.x = event.mouseMove.x;
					LastMousePos.y = event.mouseMove.y;

					// Вызов функции покраски кнопок в зависимости от текущей выбранной кнопки
					BtnFill(CurrBtn);	
				} 
			}
			

		}

		if (MenuStatus != EEndStatus::Menu) {
			return MenuStatus;
		}

		window.clear();

		window.draw(BackMenu);
		window.draw(Logo);
		window.draw(StartBtn);
		window.draw(SettingBtn);
		window.draw(EndBtn);
		
		window.display();
	}
	return EEndStatus::GameError;
}

const sf::Int32 IMainMenu::getSelectedLvl()
{
	return SelectedLvl;
}
