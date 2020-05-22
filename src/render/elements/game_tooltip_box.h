#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <neither/either.hpp>

#include "../../model/EntityType.h"

class GameTooltipBox {
private:
    int x, y, w, h;

    int visible_ticks;
    std::string text;
    std::shared_ptr<ALLEGRO_FONT> font;
public:
    GameTooltipBox() = default;
    GameTooltipBox(int center_x, int center_y, int width, int height,
               std::shared_ptr<ALLEGRO_FONT> tooltip_font
    ) : x(center_x), y(center_y), w(width), h(height), visible_ticks(0),
        text(), font(tooltip_font) {}

    void show_text(std::string new_text) { visible_ticks = 90; text = new_text; }
    void reset() { visible_ticks = 0; }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);

    void render_tooltip();
};