#pragma once

#include <memory>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class GameStatusBar {
private:
    int x, y, width;
    int percent_filled;
    std::string label;
    std::shared_ptr<ALLEGRO_FONT> font;
public:
    GameStatusBar() = default;
    GameStatusBar(
        int center_x, int center_y, int full_width, int initial_fill_percent,
        std::string label_text, std::shared_ptr<ALLEGRO_FONT> status_font
    ) : x(center_x), y(center_y), width(full_width), percent_filled(initial_fill_percent),
        label(label_text), font(status_font) {}
    
    void set_label(std::string new_label) { label = new_label; }
    void set_fill(int new_percent_filled) { percent_filled = new_percent_filled; }

    void render_status_bar() const;
};