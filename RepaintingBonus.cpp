#include "RepaintingBonus.h"
void RepaintingBonus::Create(std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix, std::vector<std::vector <bool>> visited, std::shared_ptr<sf::RenderWindow> window)
{
	int randIndexY[2];
	randIndexY[0] = 2;
	randIndexY[1] = -2;

	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
		{
			if (visited[i][j] == true)
			{
				if (rand() % 20 > 10)
				{
					int x = rand() % (2 - (-2)) - 2;
					int y = rand() % (2 - (-2)) - 2;
					if (abs(x) == 1 || x == 0)
					{
						y = randIndexY[rand() % 2];
					}
					int x_ = rand() % (2 - (-2)) - 2;
					int y_ = rand() % (2 - (-2)) - 2;
					if (abs(x_) == 1 || x_ == 0)
					{
						y_ = randIndexY[rand() % 2];
					}
					if (((i + x) >= 0 && (i + x) < X) && ((j + y) < X && (j + y) >= 0) && ((i + x_) >= 0 && (i + x_) < X) && ((j + y_) < X && (j + y_) >= 0))
					{
						gemMatrix[i + x][j + y]->SetColor(gemMatrix[i][j]->GetColor());
						gemMatrix[i + x_][j + y_]->SetColor(gemMatrix[i][j]->GetColor());
						gemMatrix[i][j]->SetOutline(window, sf::Color::White);
						gemMatrix[i + x][j + y]->SetOutline(window, sf::Color::White);
						gemMatrix[i + x_][j + y_]->SetOutline(window, sf::Color::White);
					}
					return;
				}
			}
		}
}
