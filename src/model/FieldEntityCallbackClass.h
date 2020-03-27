#ifndef WARP_FIELDENTITYCALLBACKCLASS_H
#define WARP_FIELDENTITYCALLBACKCLASS_H

#include <functional>
class FieldEntity;

class FieldEntityCallbackClass {
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBProduce;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBMove;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBAttack;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBDie;

public:
    explicit FieldEntityCallbackClass(std::function<void(std::shared_ptr<FieldEntity> obj)> GMProduce,
                                      std::function<void(std::shared_ptr<FieldEntity> obj)> GMMove,
                                      std::function<void(std::shared_ptr<FieldEntity> obj)> GMAttack,
                                      std::function<void(std::shared_ptr<FieldEntity> obj)> GMDie){
        this->CBProduce = GMProduce;
        this->CBMove = GMMove;
        this->CBAttack = GMAttack;
        this->CBAttack = GMDie;
    }

    void produce(std::shared_ptr<FieldEntity> obj){this->CBProduce(obj);}
    void move   (std::shared_ptr<FieldEntity> obj){this->CBMove(obj);}
    void attack (std::shared_ptr<FieldEntity> obj){this->CBAttack(obj);}
    void die    (std::shared_ptr<FieldEntity> obj){this->CBDie(obj);}
};


#endif //WARP_FIELDENTITYCALLBACKCLASS_H
