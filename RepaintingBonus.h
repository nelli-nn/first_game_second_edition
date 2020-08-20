#pragma once
#include "Bonus.h"
class RepaintingBonus : public Bonus
{
public:
	RepaintingBonus() {}
	virtual ~RepaintingBonus() {}
	void Create(std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix, std::vector<std::vector <bool>> visited, std::shared_ptr<sf::RenderWindow> window) override;
};
