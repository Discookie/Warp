#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include "Hq.h"

class HqDefense : public Hq {
public:
    HqDefense(std::pair<int, int> position, CallbackClass gameModelCallback);
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


#endif //WARP_HQDEFENSE_H
