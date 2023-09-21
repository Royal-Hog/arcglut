#ifndef CARRIAGE_H
#define CARRIAGE_H
#include "entity.h"

const int32_t CARRIAGE_WIDTH = 250;
const int32_t CARRIAGE_HEIGHT = 100;
class carriage :
    public entity
{
public:
    static carriage* Carriage;
    bool stick;
    int32_t changeSizeT;
    carriage() : entity({ CARRIAGE_WIDTH, CARRIAGE_HEIGHT }) {
        stick = false;
        changeSizeT = -1000000;
        Carriage = this;
        size = { 50, 10 };
        FullVelocity = 50;
    }
    void DrawCarriage();
    void LeftMoving();
    void RightMoving();
    virtual PAIR getSize();
    static void BallCollide();
private:
    PAIR size;
    double FullVelocity;
};
#endif


