#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include "Field.h"
#include "EntityType.h"

#include "Stable/Factory.h"
#include "Stable/Stable1.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"

#include <vector>
#include <allegro5/allegro.h>

class GameModel {
private:
    std::vector<std::vector<Field>> fields;
    ALLEGRO_TIMER *timer;
    int points;
    int gold;
    int waveTimer;
    int waveNumber;
    bool haveSpecial;
    EntityType selectedTower;
public:
    GameModel();
    void newGame();
    void loadGame();

    Field getField(std::pair<int, int> position);
    void updateFields();
    void selectTower(EntityType type);
    bool isBuildable(EntityType type);
    void buildTower(std::pair<int, int> position);
    int getGold() const { return this->gold; }
    int getPoints() const { return this->points; }
    int getWaveNumber() const { return this->waveNumber; }
    int getWaveProgress();

    void pause();
    void resume();
};

#endif //WARP_GAMEMODEL_H
