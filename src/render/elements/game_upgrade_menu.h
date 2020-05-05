#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "game_button.h"

struct GameUpgradeCallbacks {
    std::optional<std::function<void()>> on_upgrade;
    std::optional<std::function<void()>> on_delete;
};

class GameUpgradeMenu {
    GameButton upgrade_button;
    GameButton delete_button;

    std::optional<EntityType> selected_entity;
    int center_x, center_y;
    
    GameUpgradeCallbacks callbacks;

    GameUpgradeMenu(
        int cx, int cy,
        GameButton upgrade_btn,
        GameButton delete_btn,
        GameUpgradeCallbacks callback_list
    );
public:

    static neither::Either<std::string, std::unique_ptr<GameUpgradeMenu>> create(
        int center_x, int center_y, std::shared_ptr<ALLEGRO_FONT> button_font,
        GameUpgradeCallbacks callback_list
    );

    void set_prices(std::optional<EntityType> type, bool is_upgraded);
    void set_visible(bool new_vis);
    GameUpgradeCallbacks& modify_callbacks() { return callbacks; }
    /// Enables items based on how much money you have
    void update_buyable(int money);

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_selector();
};