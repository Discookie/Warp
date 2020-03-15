#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include "Hq.h"

class HqDefense : public Hq {
public:
    explicit HqDefense(std::pair<int, int> position);
    static const int cost = 200;

    void update() override;
    void upgrade() override;
    void die() override;
    void attack() override;
    int value() override;
    void takeDamage(int amount) override;
    bool isFriendly() override { return true; }
    void getStats() override;
};


#endif //WARP_HQDEFENSE_H
