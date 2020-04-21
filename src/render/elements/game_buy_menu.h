#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <neither/either.hpp>

#include "../../model/EntityType.h"

class GameBuyButton {
private:
    int x, y, w, h;
    bool enabled;
    // FIXME: Add a Dragged state
    std::string name;
    int price;
    std::shared_ptr<ALLEGRO_FONT> font;
    std::optional<std::function<void()>> click_callback;
    std::optional<std::function<void()>> release_callback;
public:
    GameBuyButton() = default;
    GameBuyButton(int center_x, int center_y, int width, int height,
               std::string name_text, int price_value,
               std::shared_ptr<ALLEGRO_FONT> button_font,
               std::optional<std::function<void()>> on_click,
               std::optional<std::function<void()>> on_release
    ) : x(center_x), y(center_y), w(width), h(height), enabled(false),
        name(name_text), price(price_value), 
        font(button_font),
        click_callback(on_click), release_callback(on_release) {}

    void set_name(std::string new_name) { name = new_name; }
    int get_price() { return price; }
    void set_price(int new_price) { price = new_price; }
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

struct GameBuyCallbacks {
    std::optional<std::function<void(EntityType)>> select_callback;
    std::optional<std::function<void(EntityType)>> drag_callback;
    std::optional<std::function<void()>> drag_cancel_callback;
};

class GameBuyMenu {
    std::vector<GameBuyButton> items;
    int selected_item;
    int center_x, center_y;
    
    GameBuyCallbacks callbacks;

    GameBuyMenu(
        int cx, int cy,
        std::vector<GameBuyButton>&& buy_items,
        GameBuyCallbacks callback_list
    );
public:

    static neither::Either<std::string, std::unique_ptr<GameBuyMenu>> create(
        int center_x, int center_y, std::shared_ptr<ALLEGRO_FONT> button_font,
        GameBuyCallbacks callback_list
    );

    int get_selected_item() { return selected_item; }
    /// Enables items based on how much money you have
    void update_buyable(int money);


    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    //void on_hover(const ALLEGRO_MOUSE_EVENT& event);

    /// Note: Does not reset 'dragged' state on events not captured  
    /// Note: Needs to be run 'last' in the release events.
    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_selector();
};