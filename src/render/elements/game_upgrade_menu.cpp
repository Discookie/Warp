#include "game_upgrade_menu.h"
#include "../../model/Constants.h"

#include <allegro5/allegro_primitives.h>
#include <string>

const auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

using menu_ptr = std::unique_ptr<GameUpgradeMenu>;
using cost_func = std::function<int()>;

inline cost_func make_cost_func(int value) {
    return [value](){ return value; };
}
inline cost_func invert(cost_func fn) {
    return [fn](){ return -fn(); };
}


// {name, type, cost}
const std::vector<std::optional<cost_func>> item_upgrade_costs = {
        std::nullopt,
        Constants::FACTORY_UPGRADE_COST,
        Constants::LASERTOWER_UPGRADE_COST,
        Constants::TESLACOIL_UPGRADE_COST,
        Constants::SNIPERTOWER_UPGRADE_COST,
        make_cost_func(Constants::HQATTACK_UPGRADE_COST),
        make_cost_func(Constants::HQDEFENSE_UPGRADE_COST),
        make_cost_func(Constants::SPECIAL_UPGRADE_COST),
        std::nullopt,
};

const std::vector<std::optional<std::function<int()>>> item_delete_costs = {
    std::nullopt,
    make_cost_func(Constants::FACTORY_BASE_REMOVE_VALUE),
    make_cost_func(Constants::LASERTOWER_BASE_REMOVE_VALUE),
    make_cost_func(Constants::TESLACOIL_BASE_REMOVE_VALUE),
    make_cost_func(Constants::SNIPERTOWER_BASE_REMOVE_VALUE),
    make_cost_func(Constants::HQATTACK_REMOVE_VALUE),
    make_cost_func(Constants::HQDEFENSE_REMOVE_VALUE),
    make_cost_func(Constants::SPECIAL_REMOVE_VALUE),
    std::nullopt,
};

neither::Either<std::string, menu_ptr> GameUpgradeMenu::create(
    int center_x, int center_y, std::shared_ptr<ALLEGRO_FONT> button_font,
    GameUpgradeCallbacks callback_list
) {
    // FIXME: Add coin icon loading code here
    using ret_ty = neither::Either<std::string, menu_ptr>;

    const int offset = 20;
    const int center_top_y = center_y - offset / 2;

    GameButton upgrade_button(
        center_x, center_top_y, 70, offset - 4,
        "Upgrade", item_upgrade_costs[0].value_or(make_cost_func(0)), button_font,
        std::nullopt, std::nullopt
    );
    GameButton delete_button(
        center_x, center_top_y + offset, 70, offset - 4,
        "Delete", invert(item_upgrade_costs[0].value_or(make_cost_func(0))), button_font,
        std::nullopt, std::nullopt
    );
    return ret_ty::rightOf(menu_ptr(
        new GameUpgradeMenu(center_x, center_y, upgrade_button, delete_button, callback_list)
    ));
}

GameUpgradeMenu::GameUpgradeMenu(
    int cx, int cy,
    GameButton upgrade_btn,
    GameButton delete_btn,
    GameUpgradeCallbacks callback_list
) : center_x(cx), center_y(cy), 
    upgrade_button(upgrade_btn), delete_button(delete_btn),
    callbacks(callback_list)
{

    upgrade_button.set_click_callback([&](){
        if (callbacks.on_upgrade) {
            (*callbacks.on_upgrade)();
        }
    });
    delete_button.set_click_callback([&](){
        if (callbacks.on_delete) {
            (*callbacks.on_delete)();
        }
    });
    set_visible(false);
}

void GameUpgradeMenu::set_prices(std::optional<EntityType> type, bool is_upgraded) {
    int idx = type.value_or(EntityType::TypeNone);

    if (!is_upgraded && item_upgrade_costs[idx]) {
        upgrade_button.set_price(*item_upgrade_costs[idx]);
        upgrade_button.set_visible(true);
    } else {
        upgrade_button.set_visible(false);
    }

    if (item_delete_costs[idx]) {
        delete_button.set_price(*item_delete_costs[idx]);
        delete_button.set_visible(true);
    } else {
        delete_button.set_visible(false);
    }
}
void GameUpgradeMenu::set_upgrade_visible(bool new_vis) {
    upgrade_button.set_visible(new_vis);
}
void GameUpgradeMenu::set_visible(bool new_vis) {
    upgrade_button.set_visible(new_vis);
    delete_button.set_visible(new_vis);
}
void GameUpgradeMenu::update_buyable(int money) {
    upgrade_button.update_buyable(money);
    delete_button.update_buyable(money);
}


void GameUpgradeMenu::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    const int offset = 20;

    const int left = center_x - 40;
    const int right = center_x + 40;
    const int top = center_y - offset;
    const int bot = center_y + offset;

    auto is_between = [](int num, int bot, int top) { return num >= bot && num <= top; };

    if (is_between(event.x, left, right) && is_between(event.y, top, bot)) {
        upgrade_button.on_click(event);
        delete_button.on_click(event);
    }
}

void GameUpgradeMenu::on_release(const ALLEGRO_MOUSE_EVENT& event) {
    const int offset = 20;

    const int left = center_x - 40;
    const int right = center_x + 40;
    const int top = center_y - offset;
    const int bot = center_y + offset;

    auto is_between = [](int num, int low, int high) { return num >= low && num <= high; };

    if (is_between(event.x, left, right) && is_between(event.y, top, bot)) {
        upgrade_button.on_release(event);
        delete_button.on_release(event);
    }
}

void GameUpgradeMenu::render_selector() {
    upgrade_button.render_button();
    delete_button.render_button();
}
