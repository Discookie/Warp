#ifndef WARP_FIELDENTITYCALLBACKCLASS_H
#define WARP_FIELDENTITYCALLBACKCLASS_H

#include <functional>

class FieldEntity;

class FieldEntityCallbackClass {
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_produce;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_move;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_attack;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_die;

public:
    FieldEntityCallbackClass(
        std::function<void(std::shared_ptr<FieldEntity> obj)> gm_produce,
        std::function<void(std::shared_ptr<FieldEntity> obj)> gm_move,
        std::function<void(std::shared_ptr<FieldEntity> obj)> gm_attack,
        std::function<void(std::shared_ptr<FieldEntity> obj)> gm_die) {
        this->cb_produce = gm_produce;
        this->cb_move    = gm_move;
        this->cb_attack  = gm_attack;
        this->cb_attack  = gm_die;
    }

    void produce(std::shared_ptr<FieldEntity> obj) { this->cb_produce(obj); }

    void move(std::shared_ptr<FieldEntity> obj) { this->cb_move(obj); }

    void attack(std::shared_ptr<FieldEntity> obj) { this->cb_attack(obj); }

    void die(std::shared_ptr<FieldEntity> obj) { this->cb_die(obj); }
};

#endif  // WARP_FIELDENTITYCALLBACKCLASS_H
