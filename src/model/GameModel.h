#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include "Field.h"
#include "EntityType.h"
#include <vector>

class GameModel {
private:
    std::vector<std::vector<Field>> fields;
    int gold;
    int waveTimer;
    bool haveSpecial;
    EntityType selectedTower;
    int points; // ?
public:
    void updateFields();
    void selectTower(EntityType type);
    bool isBuildable(EntityType type);
    void buildTower(std::pair<int, int> pos);
    int getGold;
    int getPoints(); // ?
    int getWaveNumber();
    int getWaveProgress();

    void pause();
    void resume();
};


#endif //WARP_GAMEMODEL_H
