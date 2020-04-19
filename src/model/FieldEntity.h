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
    FieldEntity(Coordinate pos, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback){
        this->position    = pos;
        this->callback    = gameModelCallback;
        this->timeCounter = 0;
    }
    virtual ~FieldEntity() = default;
    virtual int maxHp() = 0;
    virtual int cost() = 0;
    virtual int attackSpeed() = 0;
    virtual int damage() = 0;

    // Getters
    virtual bool isFriendly() = 0;
    Coordinate getPosition() { return position; }
    /// Returns the index of a given unstable object inside the MovingEntities vector or -1 if its a Tower object.
    virtual int getVectorPos() = 0;
    // virtual void getStats() = 0; // Stats class???

    // Action functions
    void update() { timeCounter++; doActions(); }
    virtual void doActions() = 0;
    void attack() { callback->attack(shared_from_this()); }
    virtual void takeDamage(int amount) { this->hp -= amount; if(hp < 0){ this->die(); }}
    void die() { callback->die(shared_from_this()); }
};

#endif //WARP_FIELDENTITY_H
