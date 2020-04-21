#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Factory : public Stable {
public:
    Factory(Coordinate position,
            const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback){
        this->upgraded = false;
        this->hp = Constants::FACTORY_MAX_HP;
    }

    int max_hp() override { return Constants::FACTORY_MAX_HP; }

    int cost() override { return Constants::FACTORY_BASE_COST; }

    int upgrade_cost() override { return Constants::FACTORY_UPGRADE_COST; }

    int attack_speed() override { return Constants::FACTORY_ATTACK_SPEED; }

    int damage() override { return Constants::FACTORY_DAMAGE; }

    void attack_entities(std::vector<std::vector<Field>> &) override {}

    int production_amount() {
        return !upgraded ?
               Constants::FACTORY_BASE_PRODUCTION : Constants::FACTORY_UPGRADE_PRODUCTION;
    }

    int production_speed() {
        return !upgraded ?
               Constants::FACTORY_BASE_PRODUCTION_SPEED : Constants::FACTORY_UPGRADE_PRODUCTION_SPEED;
    }

    void do_actions() override {
        if (time_counter % production_speed() == 0) {
            produce();
        }
    }
    void produce() { callback->produce(shared_from_this()); }
    int remove_value() override { return !upgraded ?
                                         Constants::FACTORY_BASE_REMOVE_VALUE : Constants::FACTORY_UPGRADE_REMOVE_VALUE; }
    // void getStats() override;
     EntityType get_entity_type() const override {
         return EntityType::TypeFactory;
     }
};


#endif //WARP_FACTORY_H
