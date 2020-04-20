#include "game_board.h"

#include <allegro5/allegro_primitives.h>

const std::vector<std::string> sprite_names = {
    "none",
    "factory",
    "laser_tower",
    "tesla_coil",
    "sniper_tower",
    "hq_attack",
    "hq_defense",
    "none",
    "multiple"
};

neither::Either<std::string, GameBoard> GameBoard::create(
    int center_x, int center_y,
    GameBoardCallbacks callback_list
) {
    using ret_ty = neither::Either<std::string, GameBoard>;
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

    GameBoard board(center_x, center_y, std::move(sprites), callback_list);

    return ret_ty::rightOf(std::move(board));
}

/// Each board `field` is effectively 8x8 - a 1px border around a 7px * 7px empty space.  
/// The sprite is rendered on the left top corner of the field,
/// so the left and top borders are inside the sprite.  
/// This way, we can fit more tiles on the screen while keeping an effectively 8x8 grid.
void GameBoard::render_board(const ALLEGRO_EVENT& event) {
    const int field_size = 16; // px

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

    // Create const alias for minimal perf gain
    const std::vector<std::optional<GameSprite>>& sprites = sprites;
    const std::optional<GameSprite>& multiple_sprite = *sprites.rbegin();

    int y_pos = top;

    for (int idx_y = 0; idx_y < height; idx_y++) {
        int x_pos = left;

        for (int idx_x = 0; idx_x < width; idx_x++) {
            Field& field = callbacks.get_field({idx_x, idx_y});
            EntityType ty = /* TODO: field.getTower().getType()*/ EntityType::TypeNone;
            const std::vector<std::shared_ptr<Unstable>>& entities = field.get_moving_entities();
            const std::optional<GameSprite>& sprite = sprites[ty];

            if (ty = EntityType::TypeSpecial) {
                // TODO: Render special effect bg
            } else {
                // TODO: Render default bg
            }

            if (sprite) {
                sprite->render_sprite_16px(x_pos, y_pos, event);

                // TODO: Render attacks, such as lasers, depending on attack type
                // TODO: Render HP bars

                // Multiple objects on same tile
                if (!entities.empty()) {
                    multiple_sprite->render_sprite_16px(x_pos, y_pos, event);
                }
            } else if (!entities.empty()) {
                // TODO: Render monster
                
                // TODO: Render HP bars

                // Multiple objects on same tile
                if (entities.size() > 1) {
                    multiple_sprite->render_sprite_16px(x_pos, y_pos, event);
                }
            }
        }
    }
}