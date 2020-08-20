#pragma once
#include "Project.h"
class RectangleObject
{
public:
	RectangleObject();
	virtual ~RectangleObject() {};
	COLOR GetColor();
	void SetColor(COLOR color);
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window) = 0; 
protected:
	sf::Color color;
	COLOR color_type;
	sf::Vector2f objectSize;
	sf::RectangleShape shape;
	sf::Vector2f objectPosition;
};

