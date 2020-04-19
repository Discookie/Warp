#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqDefense : public Hq {
public:
    HqDefense(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback) :
            Hq(position, game_model_callback){
        this->hp = Constants::HQDEFENSE_MAX_HP;
    }

    int max_hp() override { return Constants::HQDEFENSE_MAX_HP; }
    int cost() override { return  Constants::HQDEFENSE_BASE_COST; }
    int upgrade_cost() override { return Constants::HQDEFENSE_UPGRADE_COST; }
    int attack_speed() override { return Constants::HQDEFENSE_ATTACKSPEED; }
    int damage() override { return Constants::HQDEFENSE_DAMAGE; }
    void do_actions() override{
        if(time_counter % attack_speed() == 0){
            attack();
        }
    }

    int remove_value() override { return Constants::HQDEFENSE_REMOVE_VALUE; }
    // void getStats() override;
};


#endif //WARP_HQDEFENSE_H
