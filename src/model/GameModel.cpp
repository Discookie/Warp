#include "GameModel.h"

GameModel::GameModel(){
    this->timer = al_create_timer(1);
    GameModel::newGame();
}

void GameModel::newGame(){
    this->fields.clear();
    this->points = 0;
    this->gold = 0;
    this->waveTimer = 2000;
    this->haveSpecial = false;
    this->selectedTower = typeNone;
    this->fields.resize(5);
    for(int i = 0; i < 5; i++){
        this->fields[i].resize(8);
        for(int j = 0; j < 8; j++){
            this->fields[i][j] = Field(std::pair<int,int>(i,j));
        }
    }
    al_start_timer(this->timer);
}

void GameModel::loadGame() {
    throw std::logic_error("Unimplemented");
}

Field GameModel::getField(std::pair<int, int> position) {
    if((0 <= position.first  && position.first  < 5) &&
       (0 <= position.second && position.second < 8) ){
        this->fields[position.first][position.second];
    }

    // Implement this function with either
}

void GameModel::updateFields() {
    for(auto& v : this->fields){
        for(auto& f : v){
            f.updateEntities();
        }
    }
}

void GameModel::selectTower(EntityType type) {
    this->selectedTower = type;
}

bool GameModel::isBuildable(EntityType type) {
    switch (type) {
        case EntityType::typeFactory :
            return this->gold >= Factory::cost;
        case EntityType::typeStable_1:
            return this->gold >= Stable1::cost;
        case EntityType::typeStable_2:
            return this->gold >= Stable1::cost;
        case EntityType::typeStable_3:
            return this->gold >= Stable1::cost;
        case EntityType::typeHqAttack:
            return this->gold >= HqAttack::cost;
        case EntityType::typeHqDefense:
            return this->gold >= HqDefense::cost;
        case EntityType::typeSpecial:
            return this->gold >= Special::cost &&
                   this->haveSpecial;
        default: return false;
    }
}

void GameModel::buildTower(std::pair<int, int> position) {
    if(isBuildable(selectedTower)) {
        // Implemented with either
        //if(getField(position) == empty)
            this->fields[position.first][position.second].buildTower(selectedTower);
        //}
    }
}

int GameModel::getWaveProgress() {
    throw std::logic_error("Unimplemented");
}

void GameModel::pause() {
    al_stop_timer(this->timer);
}

void GameModel::resume() {
    al_resume_timer(this->timer);
}




