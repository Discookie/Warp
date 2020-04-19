#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
    int vector_position;
public:
    Unstable(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback, int vector_pos) :
        FieldEntity(position, game_model_callback) {
        this->vector_position = vector_pos;
    }
    ~Unstable() override = default;
    virtual int move_speed() = 0;
    void move() { callback->move(shared_from_this()); }
    void do_actions() final {
        if(time_counter % attack_speed() == 0){
            attack();
        }
        if(time_counter % move_speed() == 0){
            move();
        }
    }
};


#endif //WARP_UNSTABLE_H
