#ifndef BALL_H
#define BALL_H
#include "entity.h"
class ball :
    public entity
{
public:
    static ball* ExitingBall;
    bool sticking;
    bool protection;
    int32_t ChangeSpeed;

    ball() : entity({ 0.0, 0.0 }) {
        ExitingBall = this;
        sticking = true;
        protection = false;
        FullVelocity = 0.15;
        ChangeSpeed = -1000000;
        radius = 10;
    }
    void drawBall();
    void Bounce(PAIR cont, entity* v);
    virtual void move() override;
    virtual PAIR getSize() override;
    ~ball()
    {
        ExitingBall = NULL;
    }

private:
    double radius;
    double FullVelocity;
};
#endif