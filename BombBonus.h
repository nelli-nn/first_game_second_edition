#pragma once
#include "Project.h"
#include "Bonus.h"
class BombBonus : public Bonus
{
public:
	BombBonus() {}
	virtual ~BombBonus() {}
	void Create(std::vector<std::vector<std::shared_ptr<Gem>>> gemMatrix, std::vector<std::vector <bool>> visited, std::shared_ptr<sf::RenderWindow>) override;
};
