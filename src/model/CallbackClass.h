#ifndef WARP_CALLBACKCLASS_H
#define WARP_CALLBACKCLASS_H



class CallbackClass {
    /*
    void (*cBproduce)(std::shared_ptr<Stable> obj);
    void (*cBattack) (std::shared_ptr<Stable> obj);
    void (*cBdie)    (std::shared_ptr<Stable> obj);
     */
public:
    CallbackClass(){}
    /*
    explicit CallbackClass(void (* gmCBproduce)(std::shared_ptr<Stable> obj),
                           void (* gmCBattack) (std::shared_ptr<Stable> obj),
                           void (* gmCBdie)    (std::shared_ptr<Stable> obj)){
        this->cBproduce = gmCBproduce;
        this->cBattack  = gmCBattack;
        this->cBdie     = gmCBdie;
    }

    void produce(std::shared_ptr<Stable> obj){ cBproduce(obj); }
    void attack(std::shared_ptr<Stable> obj) { cBattack(obj);  }
    void die(std::shared_ptr<Stable> obj)    { cBdie(obj);     }
     */
    void produce(){}
    void move(){}
    void attack(){}
    void die(){}
};


#endif //WARP_CALLBACKCLASS_H
