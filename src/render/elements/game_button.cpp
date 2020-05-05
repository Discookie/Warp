#include "game_button.h"
#include "../../model/Constants.h"

#include <allegro5/allegro_primitives.h>
#include <string>

const auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

bool GameButton::update_buyable(int money) {
    enabled = money >= price();
    return enabled;
}

void GameButton::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    if (enabled && visible
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)
    ) {
        if (click_callback) {
            (*click_callback)();
        }
    }
}

void GameButton::on_release(const ALLEGRO_MOUSE_EVENT& event) {
    if (enabled && visible
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)
    ) {
        if (release_callback) {
            (*release_callback)();
        }
    }
}

void GameButton::render_button() {
    if (!visible) return;
    
    int font_height = al_get_font_line_height(font.get());

    if (enabled) {
        al_draw_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(203, 214, 137), 1
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x, y - 10, ALLEGRO_ALIGN_CENTRE,
            name.c_str()
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x + 20, y - 2, ALLEGRO_ALIGN_RIGHT,
            std::to_string(price()).c_str()
        );
    } else {
        al_draw_filled_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(99, 99, 99));
        al_draw_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(175, 175, 175), 1);
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x, y - 10, ALLEGRO_ALIGN_CENTRE,
            name.c_str()
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x + 20, y - 2, ALLEGRO_ALIGN_RIGHT,
            std::to_string(price()).c_str()
        );
    }
}