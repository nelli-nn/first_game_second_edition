#include "Gem.h"
Gem::Gem(int x, int y)
{
	objectPosition.x = x * 70;
	objectPosition.y = y * 70;
	objectSize.x = GEM_WIDTH;
	objectSize.y = GEM_HEIGHT;
	color_type = (COLOR)(rand() % 6);

	this->shape.setOutlineThickness(WIDTH);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setSize(objectSize);
	this->shape.setPosition(objectPosition);
}
void Gem::SetOutline(std::shared_ptr<sf::RenderWindow> window, sf::Color color)
{
	this->shape.setOutlineColor(color);
}
void Gem::Draw(std::shared_ptr<sf::RenderWindow> window) 
{
	switch (color_type)
	{
	case COLOR::YELLOW:
		color = sf::Color::Yellow;
		break;
	case COLOR::BLACK:
		color = sf::Color::Black;
		break;
	case COLOR::BLUE:
		color = sf::Color::Blue;
		break;
	case COLOR::CYAN:
		color = sf::Color::Cyan;
		break;
	case COLOR::GREEN:
		color = sf::Color::Green;
		break;
	case COLOR::MAGENTA:
		color = sf::Color::Magenta;
		break;
	case COLOR::RED:
		color = sf::Color::Red;
		break;
	case COLOR::WHITE:
		color = sf::Color::White;
		break;
	default:
		return;
	};
	this->shape.setFillColor(color);
	window->draw(this->shape);
}