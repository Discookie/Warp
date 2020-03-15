#ifndef WARP_STABLE1_H
#define WARP_STABLE1_H

#include "Stable.h"

class Stable1 : public Stable{
public:
    explicit Stable1(std::pair<int, int> position);
    static const int cost = 100;
    static const int upgradeCost = 100;

    void update() override;
    void upgrade() override;
    void die() override;
    void attack() override;
    int value() override;
    void takeDamage(int amount) override;
    bool isFriendly() override { return true; }
    void getStats() override;
};


#endif //WARP_STABLE1_H
