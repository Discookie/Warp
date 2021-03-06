#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include <iostream>

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
    int vector_position;

    // Actions
    void do_actions() final {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
        if (time_counter % move_speed() == 0) {
            move();
        }
    }

    void move() { callback->move(shared_from_this()); }

public:
    Unstable(
            Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback,
            int vector_pos)
            : FieldEntity(position, game_model_callback) {
        this->vector_position = vector_pos;
    }

    virtual ~Unstable() = default;

    int get_vector_pos() const final { return vector_position; }

    void set_vector_pos(int position) { this->vector_position = position; }

    virtual int move_speed() const = 0;


    // should set this->position to the new position, and return it
    // should only be called by move callback
    // if cant move, should return {}
    virtual std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &) = 0;


    friend std::ostream &operator<<(std::ostream &os, const Unstable &unstable) {
        os << unstable.position << "\n"
           << unstable.time_counter << "\n"
           << unstable.hp << "\n"
           << unstable.vector_position;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Unstable &unstable) {
        is >> unstable.position >> unstable.time_counter >> unstable.hp >> unstable.vector_position;
        return is;
    }

    bool operator==(const Unstable &rhs) const {
        return position == rhs.position && time_counter == rhs.time_counter && hp == rhs.hp
               && vector_position == rhs.vector_position
               && get_entity_type() == rhs.get_entity_type();
    }
};

#endif  // WARP_UNSTABLE_H
