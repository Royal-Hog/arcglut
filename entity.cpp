#include "entity.h"
#include "game.h"
#include <ctime>
int32_t entity::durationOfBonuses;
void entity::setPosition(PAIR pos) {
	this->position = pos;
}
void entity::BonusesDuration() {
	durationOfBonuses = 200000;
}
PAIR entity::getPosition() {
	return this->position;
}
PAIR entity::getSpeed() {
	return this->speed;
}
void entity::setSpeed(PAIR speed) {
	this->speed = speed;
}
int entity::takeChance(int n) {
	int32_t chance_int = (rand() + time(NULL)) % n;
	return chance_int;
}
PAIR contact(entity* EntityNum1, entity* EntityNum2) {
	PAIR Intersection;
	if (EntityNum1->getPosition().x > EntityNum2->getPosition().x) {
		std::swap(EntityNum1, EntityNum2);
	}
	if (EntityNum1->getPosition().x + EntityNum1->getSize().x / 2 >=
		EntityNum2->getPosition().x - EntityNum2->getSize().x / 2) {
		Intersection.x = EntityNum1->getPosition().x + EntityNum1->getSize().x / 2 -
			EntityNum2->getPosition().x - EntityNum2->getSize().x / 2;
		if (EntityNum1->getPosition().y > EntityNum2->getPosition().y) {
			std::swap(EntityNum1, EntityNum2);
		}
		if (EntityNum1->getPosition().y + EntityNum1->getSize().y / 2 >=
			EntityNum2->getPosition().y - EntityNum2->getSize().y / 2) {
			Intersection.y = EntityNum1->getPosition().y + EntityNum1->getSize().y / 2 -
				EntityNum2->getPosition().y - EntityNum2->getSize().y / 2;
			return Intersection;
		}
	}
	return EMPTY_PAIR;
}

void entity::move() {
	position.x += speed.x;
	position.y += speed.y;
	bounceOff();
}

bool entity::alife() {
	return !(position.y < 0);
}

void entity::bounceOff() {
	if (position.x + getSize().x / 2 > game::G->getWindowSize().x || position.x - getSize().x / 2 < 0) {
		speed.x *= -1;
	}
	if (position.y + getSize().y / 2 > game::G->getWindowSize().y) {
		speed.y *= -1;
	}
}
