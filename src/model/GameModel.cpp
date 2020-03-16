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
    this->constructFields();
    al_start_timer(this->timer);
}

void GameModel::loadGame() {
    throw std::logic_error("Unimplemented");
}

void GameModel::constructFields() {
    this->fields.resize(10);
    for(int i = 0; i < 10; i++) {
        this->fields[i].resize(12);
        for(int j = 0; j < 12; j++) {
            this->fields[i][j] = Field(std::pair<int,int>(i,j));
        }
    }
}

std::optional<Field> GameModel::getField(std::pair<int, int> position) {
    if((0 <= position.first  && position.first  < 10) &&
       (0 <= position.second && position.second < 12) ){
        return this->fields[position.first][position.second];
    }
    return std::nullopt;
}

void GameModel::updateModel() {
    this->updateFields();


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
        case EntityType::typeFactory  :
            return this->gold >= Factory::cost;
        case EntityType::typeStable_1 :
            return this->gold >= Stable1::cost;
        case EntityType::typeStable_2 :
            return this->gold >= Stable1::cost;
        case EntityType::typeStable_3 :
            return this->gold >= Stable1::cost;
        case EntityType::typeHqAttack :
            return this->gold >= HqAttack::cost;
        case EntityType::typeHqDefense:
            return this->gold >= HqDefense::cost;
        case EntityType::typeSpecial  :
            return this->gold >= Special::cost &&
                   this->haveSpecial;
        default: return false;
    }
}

void GameModel::buildTower(std::pair<int, int> position) {
    if( isBuildable(selectedTower) &&
        getField(position).has_value() &&
        getField(position)->getTeamStatus() != Team::Enemy) {
        this->fields[position.first][position.second].buildTower(selectedTower);
        this->gold -= this->fields[position.first][position.second].getTower().value()->cost;
        // this->points += 100;
    }
    else{
        // You can't build here!
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
