#ifndef BLOCK_H
#define BLOCK_H
#include "entity.h"
#define absolut 5
class block :
    public entity
{
public:
    static std::set<block*> BlockList;
    block(PAIR pos) : entity(pos) {
        size = { 50, 25 };
        int32_t generated_chance = takeChance(10);
        if (generated_chance == 1) setSpeed({ 0.05, 0.0 });
        hp = takeChance(absolut) + 1;
        BlockList.insert(this);
    }
    ~block() {
        BlockList.erase(this);
        CreateBonus();
    }
    static void BlockMoving();
    static void BallCollide();
    static void BlockCollide();
    static void setSize(PAIR s);
    static void DrawCurrentBlocks();
    void DrawBlock();
    virtual PAIR getSize() override;
    int32_t getHP();
private:
    int32_t hp;
    void CreateBonus();
    static PAIR size;
};
#endif
