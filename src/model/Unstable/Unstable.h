#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
    int vectorPosition;
public:
    Unstable(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
        FieldEntity(position, gameModelCallback) {
        this->vectorPosition = vectorPos;
    }
    ~Unstable() override = default;
    virtual int moveSpeed() = 0;
    void move() { callback->move(shared_from_this()); }
    void doActions() final {
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
        if(timeCounter % moveSpeed() == 0){
            move();
        }
    }
};


#endif //WARP_UNSTABLE_H
