#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <bits/unique_ptr.h>
#include "Stable.h"

class Factory : public Stable {
private:
    int production;
public:
    explicit Factory(std::pair<int, int> position);
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


#endif //WARP_FACTORY_H
