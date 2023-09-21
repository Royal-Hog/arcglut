#ifndef BONUS_H
#define BONUS_H
#include "entity.h"
class bonus :
    public entity
{
public:
    static std::set<bonus*> Bonuses;
    bonus(PAIR pos) : entity(pos, { 0, -0.1 }) {
        SetRadius(5);
        Bonuses.insert(this);
    }
    ~bonus() {
        Bonuses.erase(this);
    }
    virtual void drawBonus() = 0;
    virtual void activate() = 0;
    virtual PAIR getSize();
    static void DrawBonuses();
    static void SetRadius(double r);
    static void CarriageCollide();
    static void BonusMoving();
protected:
    static double radius;
};
#endif


