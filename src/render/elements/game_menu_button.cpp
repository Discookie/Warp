#include "game_menu_button.h"

#include <allegro5/allegro_primitives.h>

#include <iostream>

void GameMenuButton::render_button() const {
    int font_height = al_get_font_line_height(font.get());

    if (enabled) {
        al_draw_filled_rectangle(
            x - w / 2,        //
            y - h / 2,        //
            x + (w + 1) / 2,  //
            y + (h + 1) / 2,  //
            al_map_rgb(0, 0, 0));
        al_draw_rectangle(
            x - w / 2,        //
            y - h / 2,        //
            x + (w + 1) / 2,  //
            y + (h + 1) / 2,  // So that odd widths/heights are correct px long
            al_map_rgb(161, 77, 67), 1);
        al_draw_text(
            font.get(),                 //
            al_map_rgb(255, 255, 255),  //
            x,                          //
            y - font_height / 2,        //
            ALLEGRO_ALIGN_CENTRE,       //
            text.c_str());
    } else {
        al_draw_filled_rectangle(
            x - w / 2,        //
            y - h / 2,        //
            x + (w + 1) / 2,  //
            y + (h + 1) / 2,  //
            al_map_rgb(99, 99, 99));
        al_draw_rectangle(
            x - w / 2,        //
            y - h / 2,        //
            x + (w + 1) / 2,  //
            y + (h + 1) / 2,  //
            al_map_rgb(161, 77, 67), 1);
        al_draw_text(
            font.get(),                 //
            al_map_rgb(175, 175, 175),  //
            x,                          //
            y - font_height / 2,        //
            ALLEGRO_ALIGN_CENTRE,       //
            text.c_str());
    }
}

void GameMenuButton::on_click(const ALLEGRO_MOUSE_EVENT &event) {
    auto is_between = [](int num, int bot, int top) { return num >= bot && num <= top; };

    if (enabled  //
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)) {
        if (callback) {
            (*callback)();
        }
    }
}