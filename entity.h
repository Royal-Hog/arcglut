#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <set>
#define PAIR std::pair<double, double>
#define x first
#define y second
#define EMPTY_PAIR PAIR(0, 0)

class entity
{
public:
	entity(PAIR pos) :position(pos), speed({ 0.0, 0.0 }) {};
	entity(PAIR pos, PAIR spd) : position(pos), speed(spd) {};
	bool alife();
	friend PAIR contact(entity* el1, entity* el2);
	virtual PAIR getSize() = 0;
	virtual void move();
	PAIR getPosition();
	PAIR getSpeed();
	void setSpeed(PAIR spd);
	void setPosition(PAIR pos);
	static void BonusesDuration();
protected:
	int32_t takeChance(int n);
	static int durationOfBonuses;
	void bounceOff();
	PAIR position;
	PAIR speed;
};
#endif