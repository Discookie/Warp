#ifndef WARP_SNIPERTOWER_H
#define WARP_SNIPERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class SniperTower : public Stable{
public:
    SniperTower(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback) :
            Stable(position, game_model_callback){
        this->upgraded = false;
        this->hp = Constants::SNIPERTOWER_MAX_HP;
    }

    int max_hp() override { return Constants::SNIPERTOWER_MAX_HP; }
    int cost() override { return Constants::SNIPERTOWER_BASE_COST; }
    int upgrade_cost() override { return Constants::SNIPERTOWER_UPGRADE_COST; }
    int attack_speed() override { return !upgraded ?
                                         Constants::SNIPERTOWER_BASE_ATTACKSPEED : Constants::SNIPERTOWER_UPGRADE_ATTACKSPEED; }
    int damage() override { return !upgraded ?
                                   Constants::SNIPERTOWER_BASE_DAMAGE : Constants::SNIPERTOWER_UPGRADE_DAMAGE; }

    void do_actions() override {
        if(time_counter % attack_speed() == 0){
            attack();
        }
    }
    int remove_value() override {return !upgraded ?
                                        Constants::SNIPERTOWER_BASE_REMOVE_VALUE : Constants::SNIPERTOWER_UPGRADE_REMOVE_VALUE;}
    // void getStats() override;
};


#endif //WARP_SNIPERTOWER_H
