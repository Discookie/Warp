#ifndef WARP_FIELDENTITY_H
#define WARP_FIELDENTITY_H

#include <memory>
#include <vector>

#include "Coordinate.h"
#include "FieldEntityCallbackClass.h"

class Field;

class FieldEntity : public std::enable_shared_from_this<FieldEntity> {
protected:
    Coordinate position;
    std::shared_ptr<FieldEntityCallbackClass> callback;
    int time_counter;
    int hp;

public:
    virtual ~FieldEntity() = default;

    virtual int max_hp() = 0;

    virtual int cost() = 0;

    virtual int upgrade_cost() = 0;

    virtual int attack_speed() = 0;

    // Getters
    virtual bool is_friendly() = 0;

    Coordinate get_position() { return position; }

    /// Returns the index of a given unstable object inside the MoovingEntities
    /// vector or -1 if its a Tower object.
    virtual int get_vector_pos() = 0;
    // virtual void getStats() = 0; // Stats class???

    // Action functions
    virtual void update() = 0;

    virtual void attack() = 0;

    virtual std::vector<FieldEntity>&& collect_atteced_entities(
        const std::vector<std::vector<Field>>&) = 0;

    virtual int get_damage() = 0;

    virtual void take_damage(int amount) = 0;

    virtual void die() = 0;

    // Static subclass functions
    template <class T>
    static int cost_of();

    template <class T>
    static int base_max_hp_of();

    template <class T>
    static int base_attack_of();
};

#endif  // WARP_FIELDENTITY_H
