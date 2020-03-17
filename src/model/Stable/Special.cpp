#include "Special.h"

Special::Special(std::pair<int, int> position) {

}

void Special::update() {

}

void Special::upgrade() {

}

void Special::die() {

}

void Special::attack() {

}

int Special::value() {
    return 0;
}

void Special::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
