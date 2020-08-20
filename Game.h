#pragma once

#include "Project.h"
#include "Gem.h"
#include "Bonus.h"
#include "PlayingField.h"

class Game
{
public:
	Game();
	~Game() {};
	void Run();
	void Draw();
	void DrawScore();
	bool IsRunning();
	void GameProcess();
	STATE_GAME EndGame();
	void DrawBackground();
private:
	sf::Font font;
	sf::Text text;
	int scoreTotal;
	std::string string;
	STATE_GAME gameState;
	sf::Vector2f windowSize;
	std::shared_ptr <sf::Event> event;
	std::shared_ptr<PlayingField> field;
	std::shared_ptr <sf::RenderWindow> window;
};
