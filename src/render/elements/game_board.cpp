#include "game_board.h"

#include <allegro5/allegro_primitives.h>

const std::vector<std::string> sprite_names = {
    "none",
    "factory",
    "laser",
    "tesla_coil",
    "sniper_tower",
    "hs_attac",
    "hq_deffense",
    "special",
    "alien",
    "octopus",
    "robot",
    "friendly",
    "multiple"
};

neither::Either<std::string, std::unique_ptr<GameBoard>> GameBoard::create(
    int center_x, int center_y,
    GameBoardCallbacks callback_list
) {
    using ret_ty = neither::Either<std::string, std::unique_ptr<GameBoard>>;
    using vec_opt = neither::Either<std::string, std::vector<GameSprite>>;
    using sprite_opt = neither::Either<std::string, GameSprite>;

    std::vector<std::optional<GameSprite>> sprites;

    for (const auto& name : sprite_names) {
        sprite_opt new_sprite = GameSprite::create(name);

        if (new_sprite.isLeft) {
            sprites.push_back(std::nullopt);
        } else {
            sprites.push_back(std::move(new_sprite.rightValue));
        }
    }

    auto is_empty = sprites[0].has_value();

    return ret_ty::rightOf(std::unique_ptr<GameBoard>(
        new GameBoard(center_x, center_y, std::move(sprites), callback_list))
    );
}

/// Each board `field` is effectively 8x8 - a 1px border around a 7px * 7px empty space.  
/// The sprite is rendered on the left top corner of the field,
/// so the left and top borders are inside the sprite.  
/// This way, we can fit more tiles on the screen while keeping an effectively 8x8 grid.
void GameBoard::render_board(const ALLEGRO_EVENT& event) {
    const int field_size = 20; // px

    // FIXME: Ask for the active board size here
    const int width = 12;
    const int height = 10;

    const int left = x - width * field_size / 2;
    const int right = x + width * field_size / 2;
    const int top = y - height * field_size / 2;
    const int bottom = y + height * field_size / 2;


    // Render grid lines
    ALLEGRO_COLOR grid_color = al_map_rgb(175, 175, 175);
    for (
        int idx_x = 0, x_pos = left;
        idx_x <= width;
        idx_x++, x_pos += field_size
    ) {
        al_draw_line(x_pos, top, x_pos, bottom, grid_color, 1);
    }

    for (
        int idx_y = 0, y_pos = top; 
        idx_y <= height;
        idx_y++, y_pos += field_size
    ) {
        al_draw_line(left, y_pos, right, y_pos, grid_color, 1);
    }

    const std::optional<GameSprite>& multiple_sprite = *sprites.rbegin();

    int y_pos = top;

    for (int idx_y = 0; idx_y < height; idx_y++, y_pos += field_size) {
        int x_pos = left;

        for (int idx_x = 0; idx_x < width; idx_x++, x_pos += field_size) {
            const Field& field = callbacks.get_field({idx_x, idx_y});

            std::shared_ptr<const Stable> tower = field.get_tower_const();
            // This is an int instead of EntityType for easier arithmetics
            int ty = tower ? tower->get_entity_type() : EntityType::TypeNone;

            std::vector<std::shared_ptr<const Unstable>> entities = field.get_moving_entities_const();
            const std::optional<GameSprite>& sprite = sprites[ty];

            if (ty == EntityType::TypeSpecial) {
                // TODO: Render special effect bg
            } else {
                // TODO: Render default bg
            }

            // Count the entities by type
            std::vector<int> entities_found(sprite_names.size(), 0);
            for (const auto& entity : entities) {
                entities_found[entity->get_entity_type()] += 1;
            }

            // If there's a building, render it
            if (sprite) {
                auto is_empty = sprite.has_value();
                auto& sprite_clone = *sprite;
                sprite->render_sprite_16px(x_pos, y_pos, event);

                // TODO: Render attacks, such as lasers, depending on attack type
                // TODO: Render HP bars

                // For the entities, render the ribbon
                if (!entities.empty()) {
                    multiple_sprite->render_sprite_16px(x_pos, y_pos, event);
                }
            // If there's no building, render the highest-priority entity
            // Priorities: Friendly > Robot > Octopus > Alien
            } else if (!entities.empty()) {
                for (
                    ty = EntityType::TypeFriendly;
                    ty >= EntityType::TypeAlien; ty--
                ) {
                    if (entities_found[ty] > 0) {
                        if (sprites[ty]) {
                            sprites[ty]->render_sprite_16px(x_pos, y_pos, event);
                        }
                        break;
                    }
                }
                // TODO: Render HP bars

                // For the rest of the objects, render the ribbon
                if (entities.size() > 1) {
                    multiple_sprite->render_sprite_16px(x_pos, y_pos, event);
                }
            }
        }
    }
}

void GameBoard::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    const auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

    const int field_size = 20; // px

    // FIXME: Ask for the active board size here
    const int width = 12;
    const int height = 10;

    const int left = x - width * field_size / 2;
    const int right = x + width * field_size / 2;
    const int top = y - height * field_size / 2;
    const int bottom = y + height * field_size / 2;

    if (is_between(event.x, left, right) && is_between(event.y, top, bottom)) {
        Coordinate field = {
            (event.x - left) / field_size,
            (event.y - top) / field_size
        };

        // Defaults to 'true' return value
        if (!callbacks.on_select_field || (*callbacks.on_select_field)(field)) {
            selected_field = field;
        }
    }
}

void GameBoard::on_release(const ALLEGRO_MOUSE_EVENT& event) {
    
}