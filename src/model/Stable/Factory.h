#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H


#include "Stable.h"

class Factory : public Stable {
public:
    Factory(std::pair<int, int> position, CallbackClass callback);
    int maxHp() override { return 1000; }
    int cost() override { return 100; }
    int upgradeCost() override { return 100; }
    int attackSpeed() override { return 10; }
    int production() { return 50; }

    bool isFriendly() override { return true; }
    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_FACTORY_H
