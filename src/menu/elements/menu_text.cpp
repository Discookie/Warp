#include "menu_text.h"

#include <allegro5/allegro_primitives.h>
#include <iostream>

void MenuText::render_text() const {
    int font_height = al_get_font_line_height(font.get());

    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y - font_height/2,
        ALLEGRO_ALIGN_CENTRE, text.c_str()
    );
}