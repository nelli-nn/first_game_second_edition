#include "BombBonus.h"
void BombBonus::Create(std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix, std::vector<std::vector <bool>> visited, std::shared_ptr<sf::RenderWindow>)
{
	int bombs = 5;
	while (bombs)
	{
		int x = rand() % 8;
		int y = rand() % 8;
		if (gemMatrix[x][y]->GetColor() != (COLOR)8)
		{
			gemMatrix[x][y]->SetColor((COLOR)8);
			bombs--;
		}
	}
}