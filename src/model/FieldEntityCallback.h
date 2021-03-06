#ifndef WARP_FIELDENTITYCALLBACK_H
#define WARP_FIELDENTITYCALLBACK_H

#include <functional>

class FieldEntity;

class FieldEntityCallback {
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_produce;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_move;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_attack;
    std::function<void(std::shared_ptr<FieldEntity> obj)> cb_die;

public:
    FieldEntityCallback(
            std::function<void(std::shared_ptr<FieldEntity> obj)> gm_produce,
            std::function<void(std::shared_ptr<FieldEntity> obj)> gm_move,
            std::function<void(std::shared_ptr<FieldEntity> obj)> gm_attack,
            std::function<void(std::shared_ptr<FieldEntity> obj)> gm_die)
            : cb_produce(std::move(gm_produce)),
              cb_move(std::move(gm_move)),
              cb_attack(std::move(gm_attack)),
              cb_die(std::move(gm_die)) {}

    void produce(std::shared_ptr<FieldEntity> obj) { this->cb_produce(obj); }

    void move(std::shared_ptr<FieldEntity> obj) { this->cb_move(obj); }

    void attack(std::shared_ptr<FieldEntity> obj) { this->cb_attack(obj); }

    void die(std::shared_ptr<FieldEntity> obj) { this->cb_die(obj); }
};

#endif  //WARP_FIELDENTITYCALLBACK_H
