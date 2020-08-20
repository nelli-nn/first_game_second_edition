#include "PlayingField.h"
PlayingField::PlayingField() :
	countClick(0),
	visited(X, std::vector<bool>(Y, false)),
	axesOx(false),
	axesOy(false) 
{

}
int PlayingField::GetClickNumber()
{
	return countClick;
}
void PlayingField::DrawField(std::shared_ptr<sf::RenderWindow> window)
{
	for (auto& gem : gemMatrix)
	{
		for (auto& currentGem : gem)
		{
			currentGem->Draw(window);
		}
	}
}
void PlayingField::CheckClick(std::shared_ptr<sf::RenderWindow> window, int * scoreTotal)
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) {
			if (i == coordinates.y - 1 && j == coordinates.x - 1) {
				if (this->Difference()) {
					this->Swap(window);
					if (this->Combinations())
					{
						this->CheckLine(scoreTotal, window);
					}
					else
					{
						this->Swap(window);
					}
				}
				this->StartPositions();
				countClick = 0;
			}
		}
}
void PlayingField::CheckLine(int* scoreTotal, std::shared_ptr<sf::RenderWindow> window)
{
	if (this->Combinations())
	{
		this->Remove();
		int count = 8;
		while (count) {
			this->ShiftGems();
			count--;
		}
		this->FillField();
		this->GetScore(scoreTotal);
		this->CheckBonus(window);
		this->Update();
	}
}

void PlayingField::FieldOutline(std::shared_ptr<sf::RenderWindow> window)
{
	for (auto& gem : gemMatrix)
	{
		for (auto& currentGem : gem)
		{
			currentGem->SetOutline(window, sf::Color::Black);
		}
	}
}
void PlayingField::StartPositions()
{
	coordinates.x = -1;
	coordinates.y = -1;
	coordinates_next.x = -1;
	coordinates_next.y = -1;
	axesOx = axesOy = false;
}
void PlayingField::InitializeField()
{
	for (int i = 1; i <= X; i++)
	{
		std::vector <std::shared_ptr<Gem>> gem_set;
		for (int j = 1; j <= Y; j++)
		{
			gem_set.push_back(std::make_shared<Gem>(i, j));
		}
		gemMatrix.push_back(gem_set);
		gem_set.clear();
	}
}
void PlayingField::GetScore(int* scoreTotal)
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) {
			if (visited[i][j] == true) {
				(*scoreTotal)++;
			}
		}
}

bool PlayingField::Combinations()
{
	bool isCombination = false;
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
		{
			if (gemMatrix[i][j]->GetColor() != (COLOR)8) {
				if (i < X - 1 && gemMatrix[i][j]->GetColor() == gemMatrix[i + 1][j]->GetColor())
					if (i > 0 && gemMatrix[i][j]->GetColor() == gemMatrix[i - 1][j]->GetColor()) {
						visited[i - 1][j] = true;
						visited[i][j] = true;
						visited[i + 1][j] = true;
						isCombination = true;
					}

				if (j < Y - 1 && gemMatrix[i][j]->GetColor() == gemMatrix[i][j + 1]->GetColor())
					if (j > 0 && gemMatrix[i][j]->GetColor() == gemMatrix[i][j - 1]->GetColor()) {
						visited[i][j - 1] = true;
						visited[i][j] = true;
						visited[i][j + 1] = true;
						isCombination = true;
					}
			}
		}
	return isCombination;
}
void PlayingField::InitEvent(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> event)
{
	bool firstClick = false;
	bool secondClick = false;
	if (countClick == 0) {
		firstClick = true;
		secondClick = false;
	}
	else {
		firstClick = false;
		secondClick = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event->type == sf::Event::MouseButtonPressed && event->key.code == sf::Mouse::Left && countClick == 0 && firstClick) {
		point = sf::Mouse::getPosition(*window);
		coordinates.x = point.x / (GEM_WIDTH + 2 * WIDTH);
		coordinates.y = point.y / (GEM_HEIGHT + 2 * WIDTH);
		if (coordinates.x != -1)
			countClick++;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event->type == sf::Event::MouseButtonPressed && event->key.code == sf::Mouse::Left && countClick == 1 && secondClick) {
		point = sf::Mouse::getPosition(*window);

		coordinates_next.x = (float)point.x / (GEM_WIDTH + 2 * WIDTH);
		coordinates_next.y = (float)point.y / (GEM_HEIGHT + 2 * WIDTH);
		if (coordinates_next.x != coordinates.x || coordinates.y != coordinates_next.y) {
			countClick++;
			secondClick = false;
		}
	}
}

void PlayingField::Remove()
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) {
			if (visited[i][j] == true) {
				gemMatrix[i][j]->SetColor((COLOR)8);
			}
		}
}

void PlayingField::ShiftGems()
{
	for (int i = X - 1; i >= 0; i--)
	{
		for (int j = X - 1; j >= 0; j--) {
			if (gemMatrix[i][j]->GetColor() == (COLOR)8 && j > 0) {
				int l = j - 1;
				while (l > 1 && gemMatrix[l][j]->GetColor() == (COLOR)8) {
					l = l - 1;
				}
				gemMatrix[i][j]->SetColor(gemMatrix[i][l]->GetColor());
				gemMatrix[i][l]->SetColor((COLOR)8);
			}
		}
	}
}
void PlayingField::FillField()
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) {
			if (gemMatrix[i][j]->GetColor() == (COLOR)8) {
				gemMatrix[i][j]->SetColor((COLOR)(rand() % 7));
			}
		}
}
void PlayingField::Update()
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) {
			visited[i][j] = false;
		}
}

void PlayingField::SwapGemsOx(std::shared_ptr<sf::RenderWindow> window)
{
	COLOR tmp = gemMatrix[coordinates_next.x - 1][coordinates_next.y - 1]->GetColor();
	gemMatrix[coordinates_next.x - 1][coordinates_next.y - 1]->SetColor(gemMatrix[coordinates.x - 1][coordinates.y - 1]->GetColor());
	gemMatrix[coordinates.x - 1][coordinates.y - 1]->SetColor(tmp);
	gemMatrix[coordinates.x - 1][coordinates.y - 1]->SetOutline(window, sf::Color::White);
	gemMatrix[coordinates_next.x - 1][coordinates_next.y - 1]->SetOutline(window, sf::Color::White);
}

void PlayingField::SwapGemsOy(std::shared_ptr<sf::RenderWindow> window)
{
	COLOR tmp = gemMatrix[coordinates.x - 1][coordinates_next.y - 1]->GetColor();
	gemMatrix[coordinates.x - 1][coordinates_next.y - 1]->SetColor(gemMatrix[coordinates.x - 1][coordinates.y - 1]->GetColor());
	gemMatrix[coordinates.x - 1][coordinates.y - 1]->SetColor(tmp);
	gemMatrix[coordinates.x - 1][coordinates.y - 1]->SetOutline(window, sf::Color::White);
	gemMatrix[coordinates.x - 1][coordinates_next.y - 1]->SetOutline(window, sf::Color::White);
}

void PlayingField::Swap(std::shared_ptr<sf::RenderWindow> window)
{
	if (axesOx)
		this->SwapGemsOx(window);
	else if (axesOy)
		this->SwapGemsOy(window);
}
bool PlayingField::Difference()
{
	if (abs(coordinates.x - coordinates_next.x) == 1 && abs(coordinates.y - coordinates_next.y) == 0) {
		axesOx = true;
		return true;
	}
	else if (abs(coordinates.x - coordinates_next.x) == 0 && abs(coordinates.y - coordinates_next.y) == 1) {
		axesOy = true;
		return true;
	}
	return false;
}
void PlayingField::CheckBonus(std::shared_ptr<sf::RenderWindow> window)
{
	if (rand() % (REPAINTING_PROBABILITY + 5) > REPAINTING_PROBABILITY) {
		repainting = std::make_shared<RepaintingBonus>();
		repainting->Create(gemMatrix, visited, window);
	}
	else if (rand() % (BOMB_PROBABILITY + 5) > BOMB_PROBABILITY)
	{
		bomb = std::make_shared<BombBonus>();
		bomb->Create(gemMatrix, visited, window);
	}
}