#include "game_status_bar.h"

#include <allegro5/allegro_primitives.h>

void GameStatusBar::render_status_bar() const {
    int fill_width = x + width * (percent_filled - 50) / 100;

    if (percent_filled > 100) {
        al_draw_filled_rectangle(
            x - width / 2, y,
            x + width / 2, y + 8,
            al_map_rgb(79, 68, 156)
        );
    } else {
        al_draw_filled_rectangle(
            x - width / 2, y,
            fill_width, y + 8,
            al_map_rgb(155, 227, 157)
        );
    }
    al_draw_rectangle(
        x - width / 2, y,
        x + width / 2, y + 8,
        al_map_rgb(175, 175, 175), 1
    );

    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y - 11, ALLEGRO_ALIGN_CENTRE,
        label.c_str()
    );
}