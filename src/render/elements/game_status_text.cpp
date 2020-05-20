#include "game_status_text.h"

void GameStatusText::render_text() const {
    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y - 11, ALLEGRO_ALIGN_CENTRE, label.c_str()
    );

    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y, ALLEGRO_ALIGN_CENTRE, value.c_str()
    );
}