#include "Field.h"

#include <iostream>
#include <utility>

#include "Stable/Factory.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/LaserTower.h"
#include "Stable/SniperTower.h"
#include "Stable/Special.h"
#include "Stable/TeslaCoil.h"
#include "Unstable/Alien.h"
#include "Unstable/Friendly.h"
#include "Unstable/Octopus.h"
#include "Unstable/Robot.h"

Field::Field(Coordinate position, std::shared_ptr<FieldEntityCallback> game_model_callback)
    : position(position),
      callback(std::move(game_model_callback)),
      team_status(Team::TeamNeutral),
      tower(nullptr),
      moving_entities(std::vector<std::shared_ptr<Unstable>>()) {}

int Field::add_unstable(EntityType et) {
    switch (et) {
        case TypeAlien:
            moving_entities.push_back(
                std::make_shared<Alien>(Alien(position, callback, moving_entities.size())));
            break;
        case TypeOctopus:
            moving_entities.push_back(
                std::make_shared<Octopus>(Octopus(position, callback, moving_entities.size())));
            break;
        case TypeRobot:
            moving_entities.push_back(
                std::make_shared<Robot>(Robot(position, callback, moving_entities.size())));
            break;
        case TypeFriendly:
            moving_entities.push_back(
                std::make_shared<Friendly>(Friendly(position, callback, moving_entities.size())));
            break;
        default:
            throw std::invalid_argument("Illegal entity type");
    }
    return moving_entities.size() - 1;
}


void Field::build_tower(EntityType type) {
    if (this->team_status == Team::TeamEnemy) {
        throw std::invalid_argument("TeamEnemy territory");
    }
    if (this->tower) {
        throw std::invalid_argument("Tower space occupied");
    }
    if (type == EntityType::TypeHqAttack || type == EntityType::TypeHqDefense) {
        if (this->position.x != 0) {
            throw std::invalid_argument("You can't build HQ here");
        }
    } else {
        if (this->position.x == 0) {
            throw std::invalid_argument("You can only build HQ here");
        }
    }
    switch (type) {
        case EntityType::TypeFactory:
            this->tower = std::make_shared<Factory>(this->position, this->callback);
            break;
        case EntityType::TypeLaserTower:
            this->tower = std::make_shared<LaserTower>(this->position, this->callback);
            break;
        case EntityType::TypeTeslaCoil:
            this->tower = std::make_shared<TeslaCoil>(this->position, this->callback);
            break;
        case EntityType::TypeSniperTower:
            this->tower = std::make_shared<SniperTower>(this->position, this->callback);
            break;
        case EntityType::TypeHqAttack:
            this->tower = std::make_shared<HqAttack>(this->position, this->callback);
            break;
        case EntityType::TypeHqDefense:
            this->tower = std::make_shared<HqDefense>(this->position, this->callback);
            break;
        case EntityType::TypeSpecial:
            this->tower = std::make_shared<Special>(this->position, this->callback);
            break;
        default:
            return;
    }
    this->team_status = Team::TeamFriendly;
}

void Field::upgrade_tower() {
    if (!this->tower) {
        throw std::invalid_argument("No tower to upgrade");
    }
    if (this->tower->is_upgraded()) {
        throw std::invalid_argument("Tower already upgraded");
    }
    if (this->tower) this->tower->upgrade();
}

void Field::remove_tower() {
    if (!this->tower) {
        throw std::invalid_argument("No tower to remove");
    }
    this->tower = nullptr;
    if (this->moving_entities.empty()) {
        this->team_status = Team::TeamNeutral;
    }
}

std::shared_ptr<Stable> Field::get_tower() { return this->tower; }

std::shared_ptr<const Stable> Field::get_tower_const() const { return this->tower; }

void Field::spawn_moving_entity(EntityType type) {
    if (this->team_status != Team::TeamFriendly && type != EntityType::TypeFriendly) {
        add_unstable(type);
        this->team_status = Team::TeamEnemy;
    } else if (this->team_status != Team::TeamEnemy && type == EntityType::TypeFriendly) {
        add_unstable(type);
        this->team_status = Team::TeamFriendly;
    }
}

void Field::add_moving_entity(std::shared_ptr<Unstable> obj) {
    if (obj->is_friendly() && this->team_status == Team::TeamEnemy) {
        throw std::invalid_argument("Team status error");
    }
    if (!obj->is_friendly() && this->team_status == Team::TeamFriendly) {
        throw std::invalid_argument("Team status error");
    }
    if (this->team_status == Team::TeamNeutral) {
        this->team_status = obj->is_friendly() ? Team::TeamFriendly : Team::TeamEnemy;
    }
    this->moving_entities.push_back(obj);
}

bool Field::remove_entity_at(int ind) {
    if (ind >= moving_entities.size()) {
        return true;
    }
    this->moving_entities.erase(this->moving_entities.begin() + ind);
    for (int i = 0; i < this->moving_entities.size(); i++) {
        moving_entities[i]->set_vector_pos(i);
    }
    if (this->get_moving_entities().empty() && !this->get_tower_const()) {
        this->team_status = Team::TeamNeutral;
    }
    return false;
}

std::vector<std::shared_ptr<Unstable>> Field::get_moving_entities() {
    return this->moving_entities;
}

std::vector<std::shared_ptr<const Unstable>> Field::get_moving_entities_const() const {
    std::vector<std::shared_ptr<const Unstable>> copy;
    std::transform(
            this->moving_entities.begin(), this->moving_entities.end(),
            std::back_inserter(copy),
            [](std::shared_ptr<Unstable> u) -> std::shared_ptr<const Unstable> {
                return std::const_pointer_cast<const Unstable>(u);
            });
    return copy;
}

void Field::update_entities() {
    if (this->tower) {
        this->tower->update();
    }
    for (unsigned long i = 0; i < moving_entities.size(); ++i) {
        // safety checks
        moving_entities[i]->set_position(this->position);
        moving_entities[i]->set_vector_pos(i);

        unsigned long s = moving_entities.size();
        moving_entities[i]->update();
        if (s != moving_entities.size()) {
            --i;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Field &field) {
    os << field.position << "\n" << field.team_status << "\n";

    if (field.get_tower_const()) {
        os << field.get_tower_const()->get_entity_type() << " " << *field.tower << "\n";
    } else {
        os << EntityType::TypeNone << "\n";
    }

    os << field.moving_entities.size() << "\n";
    for (const std::shared_ptr<Unstable> &me : field.moving_entities) {
        os << me->get_entity_type() << " " << *me << " ";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Field &field) {
    int team_status_buffer, entity_type_buffer;
    size_t s;

    is >> field.position >> team_status_buffer;

    is >> entity_type_buffer;
    if ((EntityType)entity_type_buffer != EntityType::TypeNone) {
        field.build_tower((EntityType)entity_type_buffer);
        is >> *field.tower;
    }

    is >> s;
    field.moving_entities = std::vector<std::shared_ptr<Unstable>>();
    field.moving_entities.reserve(s);
    for (size_t i = 0; i < s; ++i) {
        is >> entity_type_buffer;
        int index = field.add_unstable((EntityType)entity_type_buffer);
        is >> *field.moving_entities[index];
    }
    return is;
}

bool Field::operator==(const Field &rhs) const {
    bool all_moving_entities_equals = moving_entities.size() == rhs.moving_entities.size();
    bool towers_equals = tower ? (rhs.tower ? *tower == *rhs.tower : false) : !rhs.tower;
    if (!all_moving_entities_equals) return false;
    for (int i = 0; i < moving_entities.size(); ++i) {
        all_moving_entities_equals =
            all_moving_entities_equals && *moving_entities[i] == *rhs.moving_entities[i];
    }

    return position == rhs.position && towers_equals && all_moving_entities_equals
           && team_status == rhs.team_status;
}

bool Field::operator!=(const Field &rhs) const { return !(rhs == *this); }
