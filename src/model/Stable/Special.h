#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include "Stable.h"

class Special : public Stable{
public:
    explicit Special(std::pair<int, int> position, CallbackClass gameModelCallback);
    int maxHp() override { return 1000; }
    int cost() override { return 100; }
    int upgradeCost() override { return 100; }
    int attackSpeed() override { return 10; }

    bool isFriendly() override { return true; }
    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_SPECIAL_H
