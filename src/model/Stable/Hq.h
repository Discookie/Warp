#ifndef WARP_HQ_H
#define WARP_HQ_H

#include "Stable.h"

class Hq : public Stable {
public:
    Hq(Coordinate position,
       const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback):
            Stable(position, gameModelCallback){
        this->upgraded = true;
    }

};


#endif //WARP_HQ_H
