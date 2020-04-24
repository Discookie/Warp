#include "game_scene.h"

#include <allegro5/allegro_ttf.h>

#include <functional>

using scene_ptr = std::unique_ptr<GameScene>;
using font_ptr = std::shared_ptr<ALLEGRO_FONT>;

neither::Either<std::string, scene_ptr> GameScene::create(GameModel& model) {
    font_ptr font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -10, 0), FontDeleter());

    auto board_click = [](Coordinate _c) {};
    auto board_drag_end = [](Coordinate _c) {};
    GameBoardCallbacks board_callbacks = {
        std::nullopt,
        std::nullopt,
        //std::bind(&GameModel::get_field_const, model, std::placeholders::_1)
        [&model = std::as_const(model)](Coordinate pos) -> const Field& {
            return model.get_field_const(pos);
        }
    };
    GameBuyCallbacks buy_callbacks = {
        std::nullopt,
        std::nullopt,
        std::nullopt
    };
    GameUpgradeCallbacks upgrade_callbacks = {
        std::nullopt,
        std::nullopt
    };

    return 
        GameBoard::create(124, 135, board_callbacks)
        .rightFlatMap([&](auto&& board_ptr) {
            return GameBuyMenu::create(283, 123, font, buy_callbacks)
                .rightMap([&board_ptr](auto&& buymenu_ptr) {
                    return std::make_tuple(std::move(board_ptr), std::move(buymenu_ptr));
                });
        }).rightFlatMap([&](auto&& tuple_board_buymenu) {
            return GameUpgradeMenu::create(283, 217, font, upgrade_callbacks)
                .rightMap([&tuple_board_buymenu](auto&& upgrade_ptr) {
                    auto&& board = std::get<0>(tuple_board_buymenu);
                    auto&& buymenu = std::get<1>(tuple_board_buymenu);
                    return std::make_tuple(std::move(board), std::move(buymenu), std::move(upgrade_ptr));
                });
        }).rightMap([&model](auto&& tuple_board_buymenu_upgrade) {
            auto&& board = std::get<0>(tuple_board_buymenu_upgrade);
            auto&& buymenu = std::get<1>(tuple_board_buymenu_upgrade);
            auto&& upgrade = std::get<2>(tuple_board_buymenu_upgrade);
            return scene_ptr(new GameScene(model, std::move(board), std::move(buymenu), std::move(upgrade)));
        });
}

GameScene::GameScene(
    GameModel& _model, std::unique_ptr<GameBoard>&& _board,
    std::unique_ptr<GameBuyMenu>&& _buy_menu, std::unique_ptr<GameUpgradeMenu> _upgrade_menu
) : model(_model), board(std::move(_board)), selected_field(std::nullopt),
    buy_menu(std::move(_buy_menu)), upgrade_menu(std::move(_upgrade_menu))
{
    GameBoardCallbacks& board_callbacks = board->modify_callbacks();
    
    board_callbacks.on_select_field = [&](Coordinate pos) {
        bool building_tower = buy_menu->get_selected_item() >= 0;

        if (building_tower) {
            std::cout << "Placed" << std::endl;
            model.build_tower(pos);
            buy_menu->clear_selection();
            set_selected_field(std::nullopt);
        } else if (selected_field) {
            std::cout << "Deselected" << std::endl;
            set_selected_field(std::nullopt);
        } else {
            std::cout << "Selected" << std::endl;
            set_selected_field(pos);
        }

        return !building_tower;
    };

    GameBuyCallbacks& buy_callbacks = buy_menu->modify_callbacks();

    buy_callbacks.select_callback = [&](EntityType type) {
        model.select_tower(type);
        set_selected_field(std::nullopt);
    };

    GameUpgradeCallbacks& upgrade_callbacks = upgrade_menu->modify_callbacks();

    upgrade_callbacks.on_upgrade = [&]() {
        if (selected_field) {
            model.upgrade_tower(*selected_field);
            // do not clear field here
        }
    };
    upgrade_callbacks.on_delete = [&]() {
        if (selected_field) {
            model.remove_tower(*selected_field);
            set_selected_field(std::nullopt);
        }
    };
}

void GameScene::set_selected_field(std::optional<Coordinate> pos) {
    if (pos) {
        std::shared_ptr<const Stable> tower = model.get_field_const(*pos).get_tower_const();
        EntityType tower_type = tower ? tower->get_entity_type() : EntityType::TypeNone;
        upgrade_menu->set_prices(tower_type);
    } else {
        upgrade_menu->set_prices(EntityType::TypeNone);
    }
    
    selected_field = pos;
}

void GameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // Tick the model
    // FIXME: Move this to a better location
    // FIXME: Reset the model on scene leave/enter
    // TODO: Track previous frame for frameskips
    model.update();
    buy_menu->update_buyable(model.get_gold());
    upgrade_menu->update_buyable(model.get_gold());

    board->render_board(event);
    buy_menu->render_selector();
    upgrade_menu->render_selector();
}

void GameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            board->on_click(event.mouse);
            buy_menu->on_click(event.mouse);
            upgrade_menu->on_click(event.mouse);
            break;
        
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            board->on_release(event.mouse);
            buy_menu->on_release(event.mouse);
            upgrade_menu->on_click(event.mouse);
            break;

        // Mouse move
        case ALLEGRO_EVENT_MOUSE_AXES:
            break;
    }
}

void GameScene::on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}