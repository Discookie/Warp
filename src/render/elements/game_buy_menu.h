#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <neither/either.hpp>

#include "../../model/EntityType.h"
#include "game_button.h"

struct GameBuyCallbacks {
    std::optional<std::function<void(EntityType)>> select_callback;
    std::optional<std::function<void(EntityType)>> drag_callback;
    std::optional<std::function<void()>> drag_cancel_callback;
};

class GameBuyMenu {
    std::vector<GameButton> items;
    int selected_item;
    int center_x, center_y;
    
    GameBuyCallbacks callbacks;

    GameBuyMenu(
        int cx, int cy,
        std::vector<GameButton>&& buy_items,
        GameBuyCallbacks callback_list
    );
public:

    static neither::Either<std::string, std::unique_ptr<GameBuyMenu>> create(
        int center_x, int center_y, std::shared_ptr<ALLEGRO_FONT> button_font,
        GameBuyCallbacks callback_list
    );

    int get_selected_item() { return selected_item; }
    void clear_selection();
    GameBuyCallbacks& modify_callbacks() { return callbacks; }
    /// Enables items based on how much money you have
    void update_buyable(int money);


    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    //void on_hover(const ALLEGRO_MOUSE_EVENT& event);

    /// Note: Does not reset 'dragged' state on events not captured  
    /// Note: Needs to be run 'last' in the release events.
    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_selector();
};