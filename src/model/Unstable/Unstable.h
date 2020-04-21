#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
    int vector_position;

public:
    Unstable(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos)
            :
            FieldEntity(position, game_model_callback) {
        this->vector_position = vector_pos;
    }

    ~Unstable() override = default;

    int get_vector_pos() override { return vector_position; }

    void set_vector_pos(int position) { this->vector_position = position; }

    virtual int move_speed() = 0;

    void move() { callback->move(shared_from_this()); }

    // should set this->position to the new position, and return it
    // should only be called by move callback
    // if cant move, should return {}
    virtual std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &) = 0;

    void do_actions() final {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
        if (time_counter % move_speed() == 0) {
            move();
        }
    }
};


#endif //WARP_UNSTABLE_H
