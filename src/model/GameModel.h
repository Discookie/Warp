#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include <vector>
#include <optional>
#include <allegro5/allegro.h>

#include "Field.h"
#include "EntityType.h"

#include "Stable/Factory.h"
#include "Stable/Stable1.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"

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
    void buildTower(std::pair<int, int> position);
    bool isBuildable(EntityType type);

    // Enemy interaction
    void spawnEnemies();

    // Getters
    std::optional<Field> getField(std::pair<int, int> position);
    int getGold() const { return this->gold; }
    int getPoints() const { return this->points; }
    int getWaveNumber() const { return this->waveNumber; }
    int getWaveProgress();

    // Time handling
    void pause();
    void resume();
};

#endif //WARP_GAMEMODEL_H
