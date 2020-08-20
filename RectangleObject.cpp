#include "RectangleObject.h"
RectangleObject::RectangleObject() : color_type((COLOR)0), color(sf::Color::White), objectSize(0.0, 0.0), objectPosition(0.0, 0.0), shape(objectSize) {}
COLOR RectangleObject::GetColor()
{
	return color_type;
}
void RectangleObject::SetColor(COLOR color)
{
	color_type = (COLOR)color;
}