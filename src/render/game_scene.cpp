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
        std::bind(&GameModel::get_field_const, model, std::placeholders::_1)
    };
    GameBuyCallbacks buy_callbacks = {
        std::nullopt,
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
        }).rightMap([&model](auto&& tuple_board_buymenu) {
            auto&& board = std::get<0>(tuple_board_buymenu);
            auto&& buymenu = std::get<1>(tuple_board_buymenu);
            return scene_ptr(new GameScene(model, std::move(board), std::move(buymenu)));
        });
}

GameScene::GameScene(GameModel& _model, std::unique_ptr<GameBoard>&& _board, std::unique_ptr<GameBuyMenu>&& _buy_menu) 
    : model(_model), board(std::move(_board)), buy_menu(std::move(_buy_menu))
{
    GameBoardCallbacks& board_callbacks = board->modify_callbacks();
    
    board_callbacks.on_select_field = [&](Coordinate pos) {
        bool building_tower = buy_menu->get_selected_item() >= 0;
        if (building_tower) {
            model.build_tower(pos);
            buy_menu->clear_selection();
        }
        return !building_tower;
    };

    GameBuyCallbacks& buy_callbacks = buy_menu->modify_callbacks();

    buy_callbacks.select_callback = [&](EntityType type) {
        model.select_tower(type);
    };
}

void GameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // Tick the model
    // FIXME: Move this to a better location
    // FIXME: Reset the model on scene leave/enter
    // TODO: Track previous frame for frameskips
    model.update();
    buy_menu->update_buyable(model.get_gold());

    board->render_board(event);
    buy_menu->render_selector();
}

void GameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            board->on_click(event.mouse);
            buy_menu->on_click(event.mouse);
            break;
        
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            board->on_release(event.mouse);
            buy_menu->on_release(event.mouse);
            break;

        // Mouse move
        case ALLEGRO_EVENT_MOUSE_AXES:
            break;
    }
}

void GameScene::on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}