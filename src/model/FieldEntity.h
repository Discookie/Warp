#ifndef WARP_FIELDENTITY_H
#define WARP_FIELDENTITY_H

#include <tuple>
#include "CallbackClass.h"

class FieldEntity {
protected:
    std::pair<int,int> position;
    CallbackClass callback;
    int timeCounter;
    int hp;
public:
    virtual ~FieldEntity() = default;
    virtual int maxHp() = 0;
    virtual int cost() = 0;
    virtual int upgradeCost() = 0;
    virtual int attackSpeed() = 0;

    virtual bool isFriendly() = 0;
    virtual void update() = 0;
    virtual void attack() = 0;
    virtual void takeDamage(int amount) = 0;
    virtual void die() = 0;
    // virtual void getStats() = 0; // Stats class???

    // Static subclass functions
    template<class T>
    static int cost_of();
    template<class T>
    static int baseMaxHp_of();
    template<class T>
    static int baseAttack_of();
};

#endif //WARP_FIELDENTITY_H
