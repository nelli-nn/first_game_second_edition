#include "Game.h"

Game::Game() :
	gameState(STATE_GAME::CONTINUING_GAME),
	windowSize({ WIDTH_WINDOW, HEIGHT_WINDOW }),
	scoreTotal(0),
	field(std::make_shared<PlayingField>())
{
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode((unsigned int)WIDTH_WINDOW, (unsigned int)HEIGHT_WINDOW), "Gems");
	this->window->setFramerateLimit(FRAMERATE_LIMIT);
	this->event = std::make_shared<sf::Event>();
	this->font.loadFromFile("FONT/TimesNewRoman.ttf");
}

void Game::GameProcess()
{
	this->Draw();
	// Проверка на комбинации
	field->CheckLine(&scoreTotal, window);
	// Если поменяли два гемса, то смотрим существуют ли комбинации
	if (field->GetClickNumber() == 2)
	{
		field->CheckClick(window, &scoreTotal);
		this->Draw();
		sf::sleep(sf::seconds(0.5));
	}
	// Заполняем поле заново до конца
	field->FillField();
	field->FieldOutline(window);
}

void Game::Run()
{
	// Инициализируем поле и начальные позиции координат мыши
	field->StartPositions();
	field->InitializeField();
	while (IsRunning())
	{
		// Смотрим событие(нажатие мыши)
		field->InitEvent(window, event);
		if (window->pollEvent(*event))
			if (event->type == sf::Event::Closed)
				window->close();
		// Запускаем основную функцию
		this->GameProcess();
		// Проверяем набрано ли для окончания игры неообходимое количество очков
		// Если да, то заканчиваем игру и ждем, когда пользователь нажмет ESC
		if (this->EndGame() == STATE_GAME::GAME_OVER)
		{
			this->DrawBackground();
			std::string textScore = "GAME OVER. The total number of points : " + std::to_string(scoreTotal);
			sf::Text text;
			text.setString(textScore);
			text.setFont(font);
			text.setCharacterSize(SIZE_FONT);
			text.setPosition(GEM_WIDTH + 2 * WIDTH, HEIGHT_WINDOW / 2.0 - 40.0);
			window->draw(text);
			window->display();
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			window->close();
		}
	}
}

bool Game::IsRunning()
{
	if (window->isOpen())
		return true;
	return false;
}

STATE_GAME Game::EndGame()
{
	field->GetScore(&scoreTotal);
	if (scoreTotal >= SCORE_WIN)
		return STATE_GAME::GAME_OVER;
	return STATE_GAME::CONTINUING_GAME;
}

void Game::DrawBackground()
{
	window->clear();
	sf::Vector2f size_back(WIDTH_WINDOW, HEIGHT_WINDOW);
	sf::RectangleShape background;
	background.setSize(size_back);
	background.setPosition(0.0, 0.0);
	background.setFillColor(sf::Color::Black);
	window->draw(background);
}
void Game::DrawScore()
{
	std::string textScore = "The total number of points : " + std::to_string(scoreTotal);
	sf::Text text;
	text.setString(textScore);
	text.setFont(font);
	text.setCharacterSize(SIZE_FONT);
	text.setPosition(TEXT_X, TEXT_Y);
	window->draw(text);
}

void Game::Draw()
{
	this->DrawBackground();
	field->DrawField(window);
	this->DrawScore();
	window->display();
}