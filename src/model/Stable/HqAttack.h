#ifndef WARP_HQATTACK_H
#define WARP_HQATTACK_H

#include "Hq.h"

class HqAttack : public Hq {
public:
    explicit HqAttack(std::pair<int, int> position);
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


#endif //WARP_HQATTACK_H
