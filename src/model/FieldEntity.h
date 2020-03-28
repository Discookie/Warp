#ifndef WARP_FIELDENTITY_H
#define WARP_FIELDENTITY_H

#include <memory>
#include "FieldEntityCallbackClass.h"
#include "Coordinate.h"

class FieldEntity : public std::enable_shared_from_this<FieldEntity> {
protected:
    Coordinate position;
    std::shared_ptr<FieldEntityCallbackClass> callback;
    int timeCounter;
    int hp;
public:
    virtual ~FieldEntity() = default;
    virtual int maxHp() = 0;
    virtual int cost() = 0;
    virtual int upgradeCost() = 0;
    virtual int attackSpeed() = 0;

    // Getters
    virtual bool isFriendly() = 0;
    Coordinate getPosition() { return position; }
    /// Returns the index of a given unstable object inside the MoovingEntities vector or -1 if its a Tower object.
    virtual int getVectorPos() = 0;
    // virtual void getStats() = 0; // Stats class???

    // Action functions
    virtual void update() = 0;
    virtual void attack() = 0;
    virtual void takeDamage(int amount) = 0;
    virtual void die() = 0;


    // Static subclass functions
    template<class T>
    static int cost_of();
    template<class T>
    static int baseMaxHp_of();
    template<class T>
    static int baseAttack_of();
};

#endif //WARP_FIELDENTITY_H
