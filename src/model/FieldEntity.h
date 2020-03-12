#ifndef WARP_FIELDENTITY_H
#define WARP_FIELDENTITY_H

#include <tuple>

class FieldEntity {
protected:
    std::pair<int,int> position;
    int timeCounter;
    int attackSpeed;
    int hp;
    const int maxHp;
    const int cost;
public:
    virtual ~FieldEntity() = default;
    virtual void update() = 0;
    virtual void attack() = 0;
    virtual void takeDamage(int amount) = 0;
    virtual void die() = 0;
    virtual bool isFriendly() = 0;
    virtual void getStats() = 0; // Stats class???
};


#endif //WARP_FIELDENTITY_H
