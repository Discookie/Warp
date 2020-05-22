#include "game_tooltip_box.h"
#include "../../model/Constants.h"

#include <allegro5/allegro_primitives.h>
#include <string>

const auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

void GameTooltipBox::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    if (visible_ticks > 0
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)
    ) {
        visible_ticks = 0;
    }
}

void GameTooltipBox::render_tooltip() {
    if (visible_ticks <= 0) return;

    --visible_ticks;
    
    int font_height = al_get_font_line_height(font.get());

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
}