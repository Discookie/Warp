#ifndef WARP_STABLE1_H
#define WARP_STABLE1_H

#include "Stable.h"

class Stable1 : public Stable{
public:
    explicit Stable1(std::pair<int, int> position);
    int cost() override { return 100; }
    static int maxHp() { return 1000; }
    static int upgradeCost() { return 100; }
    static int attackSpeed() { return 10; }

    void update() override;
    void upgrade() override;
    void die() override;
    void attack() override;
    int value() override;
    void takeDamage(int amount) override;
    bool isFriendly() override { return true; }
    // void getStats() override;
};


#endif //WARP_STABLE1_H
