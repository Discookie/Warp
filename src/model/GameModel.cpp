#include "GameModel.h"

GameModel::GameModel(){
    this->fields = std::vector(10, std::vector<Field>(12));
    GameModel::initCallbacks();
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

void GameModel::initCallbacks() {
    // Produce Callback
    auto pro = [this](const std::shared_ptr<FieldEntity>& obj) {
        this->gold += std::static_pointer_cast<Factory>(obj)->productionAmount();
    };
    // Move Callback
    auto mov = [this](const std::shared_ptr<FieldEntity>& obj) {
        // Not implemented
    };
    // Attack Callback
    auto att = [this](const std::shared_ptr<FieldEntity>& obj) {
        // Not implemented
    };
    // Die Callback
    auto die = [this](const std::shared_ptr<FieldEntity>& obj) {
        if(obj->getVectorPos() == -1) {
            this->getField(obj->getPosition()).removeTower();
        }
        else{
            this->getField(obj->getPosition()).removeEntityAt(obj->getVectorPos());
        }
    };
    callBacks = std::make_shared<FieldEntityCallbackClass>(pro,mov,att,die);
}

void GameModel::loadGame() {
    throw std::logic_error("Unimplemented");
}

void GameModel::constructFields() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            this->fields[i][j] = Field({i, j}, this->callBacks);
        }
    }
}

Field &GameModel::getField(Coordinate position) {
    if ((0 <= position.x && position.y < 10) &&
        (0 <= position.x && position.y < 12)) {
        return this->fields[position.x][position.y];
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
        case EntityType::typeFactory:
            return this->gold >= CONSTANTS::FACTORY_BASE_COST;
        case EntityType::typeLaserTower:
            return this->gold >= CONSTANTS::LASERTOWER_BASE_COST;
        case EntityType::typeTeslaCoil:
            return this->gold >= CONSTANTS::TESLACOIL_BASE_COST;
        case EntityType::typeSniperTower:
            return this->gold >= CONSTANTS::SNIPERTOWER_BASE_COST;
        case EntityType::typeHqAttack:
            return this->gold >= CONSTANTS::HQATTACK_BASE_COST;
        case EntityType::typeHqDefense:
            return this->gold >= CONSTANTS::HQDEFENSE_BASE_COST;
        case EntityType::typeSpecial:
            return this->gold >= CONSTANTS::SPECIAL_BASE_COST &&
                   this->haveSpecial;
        default: return false;
    }
}

void GameModel::buildTower(Coordinate position) {
    if (isBuildable(selectedTower) && !getField(position).getTower() &&
        getField(position).getTeamStatus() != Team::Enemy) {
        getField(position).buildTower(selectedTower);
        this->gold -= getField(position).getTower()->cost();
        // this->points += 100;
    }
    else{
        // You can't build here!
    }
}

void GameModel::upgradeTower(Coordinate position) {
    if (getField(position).getTower() &&
        !getField(position).getTower()->isUpgraded()) {
        if (this->gold >= getField(position).getTower()->upgradeCost()) {
            this->gold -= getField(position).getTower()->upgradeCost();
            getField(position).upgradeTower();
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