#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include <iostream>

#include "../FieldEntity.h"

class Stable : public FieldEntity {
protected:
    bool upgraded;

public:
    Stable(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback)
        : FieldEntity(position, game_model_callback) {}

    ~Stable() override = default;

    bool is_friendly() final { return true; }

    int get_vector_pos() final { return -1; }

    void upgrade() { upgraded = true; }

    virtual int upgrade_cost() = 0;

    bool is_upgraded() { return upgraded; }

    virtual int remove_value() = 0;

    friend std::ostream &operator<<(std::ostream &os, const Stable &stable) {
        os << stable.position << "\n"
           << stable.time_counter << "\n"
           << stable.hp << "\n"
           << stable.upgraded;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Stable &stable) {
        is >> stable.position >> stable.time_counter >> stable.hp >> stable.upgraded;
        return is;
    }

    bool operator==(const Stable &rhs) const {
        return position == rhs.position && time_counter == rhs.time_counter && hp == rhs.hp
               && upgraded == rhs.upgraded && get_entity_type() == rhs.get_entity_type();
    }

    bool operator!=(const Stable &rhs) const { return !(rhs == *this); }
};

#endif  // WARP_STABLE_H
