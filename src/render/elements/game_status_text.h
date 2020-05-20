#pragma once

#include <memory>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class GameStatusText {
private:
    int x, y, width;
    std::string label;
    std::string value;
    std::shared_ptr<ALLEGRO_FONT> font;
public:
    GameStatusText() = default;
    GameStatusText(
        int center_x, int center_y, int full_width,
        std::string label_text, std::string value_text,
        std::shared_ptr<ALLEGRO_FONT> status_font
    ) : x(center_x), y(center_y), width(full_width),
        label(label_text), value(value_text),
        font(status_font) {}
    
    void set_label(std::string new_label) { label = new_label; }
    void set_value(std::string new_value) { value = new_value; }

    void render_text() const;
};