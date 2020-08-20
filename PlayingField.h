#pragma once
#include "Project.h"
#include "Gem.h"
#include "RepaintingBonus.h"
#include "BombBonus.h"
class PlayingField
{
public:
	PlayingField();
	~PlayingField() {}

	void Remove();
	void Update();
	void ShiftGems();
	void FillField();
	bool Difference();
	bool Combinations();
	int GetClickNumber();
	void StartPositions();
	void InitializeField();
	void GetScore(int* scoreTotal);
	void Swap(std::shared_ptr<sf::RenderWindow> window);
	void DrawField(std::shared_ptr<sf::RenderWindow> window);
	void SwapGemsOx(std::shared_ptr<sf::RenderWindow> window);
	void CheckBonus(std::shared_ptr<sf::RenderWindow> window);
	void SwapGemsOy(std::shared_ptr<sf::RenderWindow> window);
	void FieldOutline(std::shared_ptr<sf::RenderWindow> window);
	void CheckLine(int* scoreTotal, std::shared_ptr<sf::RenderWindow> window);
	void CheckClick(std::shared_ptr<sf::RenderWindow> window, int* scoreTotal);
	void InitEvent(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> event);
private:
	bool axesOx;
	bool axesOy;
	int countClick;
	sf::Vector2i point;
	sf::Vector2i coordinates;
	std::shared_ptr <Gem> gem;
	sf::Vector2i coordinates_next;
	std::shared_ptr<BombBonus> bomb;
	std::vector<std::vector <bool>> visited;
	std::shared_ptr<RepaintingBonus> repainting;
	std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix;
};

