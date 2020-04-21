#ifndef WARP_FIELDENTITY_H
#define WARP_FIELDENTITY_H

#include <memory>
#include "FieldEntityCallback.h"
#include "Coordinate.h"

class Field;

class FieldEntity : public std::enable_shared_from_this<FieldEntity> {
protected:
    Coordinate position;
    std::shared_ptr<FieldEntityCallback> callback;
    int time_counter;
    int hp;
public:
    FieldEntity(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback) {
        this->position = position;
        this->callback = game_model_callback;
        this->time_counter = 0;
    }
    explicit FieldEntity(const std::shared_ptr<FieldEntityCallback> &game_model_callback)
        : callback(game_model_callback) {}
    virtual ~FieldEntity() = default;
    virtual int max_hp() = 0;
    virtual int cost() = 0;
    virtual int attack_speed() = 0;
    virtual int damage() = 0;

    // Getters
    virtual bool is_friendly() = 0;
    Coordinate get_position() const { return position; }
    /// Returns the index of a given unstable object inside the MovingEntities vector or -1 if its a Tower object.
    virtual int get_vector_pos() = 0;
    // virtual void getStats() = 0; // Stats class???

    // Action functions
    void update() { time_counter++;
        do_actions(); }
    virtual void do_actions() = 0;
    void attack() { callback->attack(shared_from_this()); }

    virtual void attack_entities(std::vector<std::vector<Field>> &) = 0;

    virtual void take_damage(int amount) {
        this->hp -= amount;
        if (hp <= 0) { this->die(); }
    }

    void die() { callback->die(shared_from_this()); }

    virtual EntityType get_entity_type() const = 0;
};

#endif //WARP_FIELDENTITY_H
