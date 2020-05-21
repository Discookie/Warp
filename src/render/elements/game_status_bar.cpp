#include "game_status_bar.h"

#include <allegro5/allegro_primitives.h>

void GameStatusBar::render_status_bar() const {
    int fill_width = x + width * (percent_filled - 50) / 100;
    al_draw_filled_rectangle(
        x - width / 2, y + 2,
        fill_width, y + 10,
        al_map_rgb(203, 214, 137)
    );
    al_draw_rectangle(
        x - width / 2, y + 2,
        x + width / 2, y + 10,
        al_map_rgb(203, 214, 137), 1
    );

    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y - 11, ALLEGRO_ALIGN_CENTRE,
        label.c_str()
    );
}