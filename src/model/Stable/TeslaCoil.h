#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class TeslaCoil : public Stable{
public:
    TeslaCoil(Coordinate position,
              const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback) :
            Stable(position, game_model_callback){
        this->upgraded = false;
        this->hp = Constants::TESLACOIL_MAX_HP;
    }

    int max_hp() override { return Constants::TESLACOIL_MAX_HP; }

    int cost() override { return Constants::TESLACOIL_BASE_COST; }

    int upgrade_cost() override { return Constants::TESLACOIL_UPGRADE_COST; }

    int attack_speed() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_ATTACKSPEED : Constants::TESLACOIL_UPGRADE_ATTACKSPEED;
    }

    int damage() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_DAMAGE : Constants::TESLACOIL_UPGRADE_DAMAGE;
    }

    void attack_entities(const std::vector<std::vector<Field>> &) override {}

    void do_actions() override {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
    }

    int remove_value() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_REMOVE_VALUE : Constants::TESLACOIL_UPGRADE_REMOVE_VALUE;
    }
    // void getStats() override;
};


#endif //WARP_TESLACOIL_H
