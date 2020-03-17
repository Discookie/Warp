#include "GameModel.h"

GameModel::GameModel(){
    //this->timer = al_create_timer(1.0 / 30.0); // 30 fps
    this->fields = std::vector(10, std::vector<Field>(12));
    GameModel::newGame();
}

void GameModel::newGame(){
    this->fields.clear();
    this->points = 0;
    this->gold = 0;
    this->waveTimer = 2000;
    this->haveSpecial = false;
    this->selectedTower = EntityType::typeNone;
    this->constructFields();
    //al_start_timer(this->timer);
}

void GameModel::loadGame() {
    throw std::logic_error("Unimplemented");
}

void GameModel::constructFields() {
    for(int i = 0; i < 10; i++) {
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
            return this->gold >= FieldEntity::cost_of<Factory>();
        case EntityType::typeStable_1 :
            return this->gold >= FieldEntity::cost_of<Stable1>();
        case EntityType::typeStable_2 :
            return this->gold >= FieldEntity::cost_of<Stable1>();
        case EntityType::typeStable_3 :
            return this->gold >= FieldEntity::cost_of<Stable1>();
        case EntityType::typeHqAttack :
            return this->gold >= FieldEntity::cost_of<HqAttack>();
        case EntityType::typeHqDefense:
            return this->gold >= FieldEntity::cost_of<HqDefense>();
        case EntityType::typeSpecial  :
            return this->gold >= FieldEntity::cost_of<Special>() &&
                   this->haveSpecial;
        default: return false;
    }
}

void GameModel::buildTower(std::pair<int, int> position) {
    if( isBuildable(selectedTower) &&
        getField(position).has_value() &&
        getField(position)->getTeamStatus() != Team::Enemy) {
        this->fields[position.first][position.second].buildTower(selectedTower);
        this->gold -= this->fields[position.first][position.second].getTower().value()->cost();
        // this->points += 100;
    }
    else{
        // You can't build here!
    }
}

int GameModel::getWaveProgress() {
    throw std::logic_error("Unimplemented");
}

/*
void GameModel::pause() {
    al_stop_timer(this->timer);
}

void GameModel::resume() {
    al_resume_timer(this->timer);
}
*/