#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <bits/unique_ptr.h>
#include "Stable.h"

class Factory : public Stable {
public:
    explicit Factory(std::pair<int, int> position);
    int cost() override { return 100; }
    static int maxHp() { return 1000; }
    static int upgradeCost() { return 100; }
    static int attackSpeed() { return 10; }
    static int production() { return 50; }

    void update() override;
    void upgrade() override;
    void die() override;
    void attack() override;
    int value() override;
    void takeDamage(int amount) override;
    bool isFriendly() override { return true; }
    // void getStats() override;
};


#endif //WARP_FACTORY_H
