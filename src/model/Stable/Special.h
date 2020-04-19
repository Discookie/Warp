#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Special : public Stable{
public:
    Special(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback) :
            Stable(position, game_model_callback) {
        this->upgraded = true;
        this->hp = Constants::SPECIAL_MAX_HP;
    }

    int max_hp() override { return Constants::SPECIAL_MAX_HP; }
    int cost() override { return Constants::SPECIAL_BASE_COST; }
    int upgrade_cost() override { return Constants::SPECIAL_UPGRADE_COST; }
    int attack_speed() override { return Constants::SPECIAL_ATTACKSPEED; }
    int damage() override { return Constants::SPECIAL_DAMAGE; }

    void do_actions() override {
        if(time_counter % attack_speed() == 0){
            attack();
            die();
        }
    }
    int remove_value() override { return Constants::SPECIAL_REMOVE_VALUE; }
    void take_damage(int amount) override {}
    // void getStats() override;
};


#endif //WARP_SPECIAL_H
