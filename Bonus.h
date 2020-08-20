#pragma once
#include "Project.h"
#include "RectangleObject.h"
#include "Gem.h"
class Bonus : public RectangleObject
{
public:
	Bonus() {};
	virtual ~Bonus() {};
	void Draw(std::shared_ptr<sf::RenderWindow> window) override {};
	virtual void Create(std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix, std::vector<std::vector <bool>> visited, std::shared_ptr<sf::RenderWindow> window) = 0;
};
