#ifndef WARP_HQ_H
#define WARP_HQ_H

#include "Stable.h"

class Hq : public Stable {
public:
    Hq(Coordinate position,
       const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback){
        this->upgraded = true;
    }
    EntityType get_entity_type() const override {
        return EntityType::TypeHq;
    }
};


#endif //WARP_HQ_H
