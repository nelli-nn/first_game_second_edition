#pragma once
#include "Project.h"
#include "RectangleObject.h"
class Gem : public RectangleObject
{
public:
	Gem() {};
	Gem(int x, int y);
	virtual ~Gem() {};
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
	void SetOutline(std::shared_ptr<sf::RenderWindow> window, sf::Color color);
};

