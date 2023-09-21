#include "bonus.h"
#include "carriage.h"
#include <GL/freeglut.h>

std::set<bonus*> bonus::Bonuses;
double bonus::radius;
void bonus::DrawBonuses() {
	for (auto bonusT : Bonuses) {
		bonusT->drawBonus();
	}
}
PAIR bonus::getSize()
{
	return { radius * 2, radius * 2 };
}
void bonus::SetRadius(double my_radius)
{
	radius = my_radius;
}

void bonus::CarriageCollide()
{
	bonus* Removing = NULL;
	for (bonus* Bonus : Bonuses)
	{
		if (Removing)
		{
			delete Removing;
			Removing = NULL;
		}
		PAIR Contacting = contact(Bonus, carriage::Carriage);
		if (Contacting != EMPTY_PAIR)
		{
			Bonus->activate();
			Removing = Bonus;
		}
	}
	if (Removing)
	{
		delete Removing;
		Removing = NULL;
	}
}

void bonus::BonusMoving()
{
	bonus* Removing = NULL;
	for (bonus* Bonus : Bonuses)
	{
		if (Removing)
		{
			delete Removing;
			Removing = NULL;
		}
		Bonus->move();
		if (!Bonus->alife()) {
			Removing = Bonus;
		}
	}
	if (Removing) {
		delete Removing;
		Removing = NULL;
	}
}