#ifndef WARP_CALLBACKCLASS_H
#define WARP_CALLBACKCLASS_H

#include <functional>
class FieldEntity;

class CallbackClass {
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBp;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBm;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBa;
    std::function<void(std::shared_ptr<FieldEntity> obj)> CBd;

public:
    explicit CallbackClass(std::function<void(std::shared_ptr<FieldEntity> obj)> CBProduce,
                           std::function<void(std::shared_ptr<FieldEntity> obj)> CBMove,
                           std::function<void(std::shared_ptr<FieldEntity> obj)> CBAttack,
                           std::function<void(std::shared_ptr<FieldEntity> obj)> CBDie){
        this->CBp = CBProduce;
        this->CBm = CBMove;
        this->CBa = CBAttack;
        this->CBd = CBDie;
    }

    void produce(std::shared_ptr<FieldEntity> obj){this->CBp(obj);}
    void move   (std::shared_ptr<FieldEntity> obj){this->CBm(obj);}
    void attack (std::shared_ptr<FieldEntity> obj){this->CBa(obj);}
    void die    (std::shared_ptr<FieldEntity> obj){this->CBd(obj);}
};


#endif //WARP_CALLBACKCLASS_H
