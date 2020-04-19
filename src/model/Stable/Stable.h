#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include "../FieldEntity.h"

class Stable : public FieldEntity {
protected:
    bool upgraded;
public:
    Stable(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback) :
        FieldEntity(position, game_model_callback) {}
    ~Stable() override = default;

    bool is_friendly() final { return true; }
    int get_vector_pos() final { return -1; }
    void upgrade() { upgraded = true; };
    virtual int upgrade_cost() = 0;
    bool is_upgraded() { return upgraded; };
    virtual int remove_value() = 0;
};


#endif //WARP_STABLE_H
