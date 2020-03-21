#include "GameModel.h"

GameModel::GameModel(){
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
}

void GameModel::loadGame() {
    throw std::logic_error("Unimplemented");
}

void GameModel::constructFields() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 12; j++) {
            this->fields[i][j] = Field(std::pair<int,int>(i,j), CallbackClass());
        }
    }
}

Field* GameModel::getField(std::pair<int, int> position) {
    if((0 <= position.first  && position.first  < 10) &&
       (0 <= position.second && position.second < 12) ){
        return &this->fields[position.first][position.second];
    }
    throw std::exception();
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
        case EntityType::typeLaserTower :
            return this->gold >= FieldEntity::cost_of<LaserTower>();
        case EntityType::typeTeslaCoil :
            return this->gold >= FieldEntity::cost_of<TeslaCoil>();
        case EntityType::typeSniperTower :
            return this->gold >= FieldEntity::cost_of<SniperTower>();
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
        getField(position)->getTower() == nullptr &&
        getField(position)->getTeamStatus() != Team::Enemy) {
        getField(position)->buildTower(selectedTower);
        this->gold -= getField(position)->getTower()->cost();
        // this->points += 100;
    }
    else{
        // You can't build here!
    }
}

void GameModel::upgradeTower(std::pair<int, int> position) {
    if(getField(position)->getTower() && !getField(position)->getTower()->getIsUpgraded()){
        if(this->gold >= getField(position)->getTower()->upgradeCost()){
            this->gold -= getField(position)->getTower()->upgradeCost();
            getField(position)->upgradeTower();
        }
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