#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <neither/either.hpp>

#include "../../model/EntityType.h"

class GameButton {
private:
    int x, y, w, h;
    bool enabled;
    bool visible;
    // FIXME: Add a Dragged state
    std::string name;
    std::function<int()> price;
    std::shared_ptr<ALLEGRO_FONT> font;
    std::optional<std::function<void()>> click_callback;
    std::optional<std::function<void()>> release_callback;
public:
    GameButton() = default;
    GameButton(int center_x, int center_y, int width, int height,
               std::string name_text, std::function<int()> price_func,
               std::shared_ptr<ALLEGRO_FONT> button_font,
               std::optional<std::function<void()>> on_click,
               std::optional<std::function<void()>> on_release
    ) : x(center_x), y(center_y), w(width), h(height), enabled(false), visible(true),
        name(name_text), price(price_func), 
        font(button_font),
        click_callback(on_click), release_callback(on_release) {}

    void set_name(std::string new_name) { name = new_name; }
    int get_price() { return price(); }
    void set_price(std::function<int()> new_price) { price = new_price; }
    void set_visible(bool new_vis) { visible = new_vis; };
    /// Returns the button's enabled state
    bool update_buyable(int money);

    void set_click_callback(std::optional<std::function<void()>> on_click) {
        click_callback = on_click;
    }
    void set_release_callback(std::optional<std::function<void()>> on_release) {
        release_callback = on_release;
    }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    // void on_hover(const ALLEGRO_MOUSE_EVENT& event);

    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_button();
};