#include "game_buy_menu.h"
#include "../../model/Constants.h"

#include <allegro5/allegro_primitives.h>
#include <string>

const auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

bool GameBuyButton::update_buyable(int money) {
    enabled = money >= price;
    return enabled;
}

void GameBuyButton::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    if (enabled
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)
    ) {
        if (click_callback) {
            (*click_callback)();
        }
    }
}

void GameBuyButton::on_release(const ALLEGRO_MOUSE_EVENT& event) {
    if (enabled
        && is_between(event.x, x - w / 2, x + (w + 1) / 2)
        && is_between(event.y, y - h / 2, y + (h + 1) / 2)
    ) {
        if (release_callback) {
            (*release_callback)();
        }
    }
}

void GameBuyButton::render_button() {
    int font_height = al_get_font_line_height(font.get());

    if (enabled) {
        al_draw_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(203, 214, 137), 1
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x, y - 10, ALLEGRO_ALIGN_CENTRE,
            name.c_str()
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x + 20, y - 2, ALLEGRO_ALIGN_RIGHT,
            std::to_string(price).c_str()
        );
    } else {
        al_draw_filled_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(99, 99, 99));
        al_draw_rectangle(
            x - w / 2,       y - h / 2,
            x + (w + 1) / 2, y + (h + 1) / 2,
            al_map_rgb(175, 175, 175), 1);
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x, y - 10, ALLEGRO_ALIGN_CENTRE,
            name.c_str()
        );
        al_draw_text(
            font.get(), al_map_rgb(255, 255, 255),
            x + 20, y - 2, ALLEGRO_ALIGN_RIGHT,
            std::to_string(price).c_str()
        );
    }
}


using menu_ptr = std::unique_ptr<GameBuyMenu>;

// {name, type, cost}
const std::vector<std::tuple<std::string, EntityType, int>> item_infos = {
    {"Factory",      EntityType::TypeFactory,     Constants::FACTORY_BASE_COST},
    {"Laser Tower",  EntityType::TypeLaserTower,  Constants::LASERTOWER_BASE_COST},
    {"Tesla Coil",   EntityType::TypeTeslaCoil,   Constants::TESLACOIL_BASE_COST},
    {"Sniper Tower", EntityType::TypeSniperTower, Constants::SNIPERTOWER_BASE_COST},
    {"HQ: Attack",   EntityType::TypeHqAttack,    Constants::HQATTACK_BASE_COST},
    {"HQ: Defense",  EntityType::TypeHqDefense,   Constants::HQDEFENSE_BASE_COST},
    {"Unit",         EntityType::TypeFriendly,    Constants::FRIENDLY_COST},
    {"Special",      EntityType::TypeSpecial,     Constants::SPECIAL_BASE_COST},
};

neither::Either<std::string, menu_ptr> GameBuyMenu::create(
    int center_x, int center_y, std::shared_ptr<ALLEGRO_FONT> button_font,
    GameBuyCallbacks callback_list
) {
    // FIXME: Add coin icon loading code here
    using ret_ty = neither::Either<std::string, menu_ptr>;

    std::vector<GameBuyButton> buy_buttons;
    const int offset = 20;
    const int center_top_y = center_y - offset * item_infos.size() / 2;

    // Intentionally shorter
    for (int i = 0; i < item_infos.size(); i++) {
        buy_buttons.push_back(GameBuyButton(
            center_x, center_top_y + offset * i, 70, offset - 4,
            std::get<0>(item_infos[i]), std::get<2>(item_infos[i]), button_font,
            std::nullopt, std::nullopt
        ));
    }
    return ret_ty::rightOf(menu_ptr(
        new GameBuyMenu(center_x, center_y, std::move(buy_buttons), callback_list)
    ));
}

GameBuyMenu::GameBuyMenu(int cx, int cy, std::vector<GameBuyButton>&& buy_items, GameBuyCallbacks callback_list)
    : center_x(cx), center_y(cy), items(std::move(buy_items)), callbacks(callback_list)
{
    for (int i = 0; i < items.size(); i++) {
        GameBuyButton& button = items[i];
        
        button.set_click_callback([&, i](){
            selected_item = i;
            if (callbacks.drag_callback) {
                EntityType ent = std::get<1>(item_infos[i]);
                (*callbacks.drag_callback)(ent);
            }
        });
        
        button.set_release_callback([&, i](){
            if (selected_item == i) {
                if (callbacks.select_callback) {
                    EntityType ent = std::get<1>(item_infos[i]);
                    (*callbacks.select_callback)(ent);
                }
            }
        });
    }
}

void GameBuyMenu::update_buyable(int money) {
    for (int i = 0; i < items.size(); i++) {
        GameBuyButton& button = items[i];
        bool enabled = button.update_buyable(money);

        if (!enabled && selected_item == i) {
            selected_item = -1;
            if (callbacks.drag_cancel_callback) {
                (*callbacks.drag_cancel_callback)();
            }
        }
    }
}

void GameBuyMenu::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    const int offset = 24;

    const int left = center_x - 42;
    const int right = center_x + 42;
    const int top = center_y - offset * item_infos.size() / 2;
    const int bot = center_y + offset * item_infos.size() / 2;

    auto is_between = [](int num, int bot, int top) { return num >= bot && num <= top; };

    if (is_between(event.x, left, right) && is_between(event.y, top, bot)) {
        for (auto& button : items) {
            button.on_click(event);
        }
    }
}

void GameBuyMenu::on_release(const ALLEGRO_MOUSE_EVENT& event) {
    const int offset = 24;

    const int left = center_x - 42;
    const int right = center_x + 42;
    const int top = center_y - offset * item_infos.size() / 2;
    const int bot = center_y + offset * item_infos.size() / 2;

    auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

    if (is_between(event.x, left, right) && is_between(event.y, top, bot)) {
        for (auto& button : items) {
            button.on_release(event);
        }
    }
}

void GameBuyMenu::render_selector() {
    for (auto& button : items) {
        button.render_button();
    }
}
