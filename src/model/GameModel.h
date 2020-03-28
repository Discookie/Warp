#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include <vector>
#include <functional>

#include "Field.h"
#include "EntityType.h"
#include "FieldEntityCallbackClass.h"

#include "Stable/Factory.h"
#include "model/Stable/LaserTower.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"
#include "Stable/TeslaCoil.h"
#include "Stable/SniperTower.h"

class GameModel {
private:
    std::vector<std::vector<Field>> fields;
    int points;
    int gold;
    int waveTimer;
    int waveNumber;
    bool haveSpecial;
    EntityType selectedTower;
    // Callbacks
    std::shared_ptr<FieldEntityCallbackClass> callBacks;
    void initCallbacks();
public:
    // Constructors
    GameModel();
    void newGame();
    void loadGame();
    void constructFields();

    // Updates
    void updateModel();
    void updateFields();

    // Building (player interaction)
    void selectTower(EntityType type);
    void buildTower(Coordinate position);
    void upgradeTower(Coordinate position);

    // Enemy interaction
    void spawnEnemies();

    // Getters
    Field& getField(Coordinate position);
    int getGold()       const { return this->gold; }
    int getPoints()     const { return this->points; }
    int getWaveNumber() const { return this->waveNumber; }
    int getWaveProgress();
    bool isBuildable(EntityType type);
};

#endif //WARP_GAMEMODEL_H
