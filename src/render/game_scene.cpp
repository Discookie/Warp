#include "game_scene.h"

#include <functional>

using scene_ptr = std::unique_ptr<GameScene>;
using font_ptr = std::shared_ptr<ALLEGRO_FONT>;

neither::Either<std::string, scene_ptr> GameScene::create(GameModel& model) {
    font_ptr font = font_ptr(al_create_builtin_font(), FontDeleter());

    auto board_click = [](Coordinate _c) {};
    auto board_drag_end = [](Coordinate _c) {};
    GameBoardCallbacks board_callbacks = {
        [](Coordinate pos) {},
        [](Coordinate pos) {},
        std::bind(&GameModel::get_field, model, std::placeholders::_1)
    };
    GameBuyCallbacks buy_callbacks = {
        std::nullopt,
        std::nullopt,
        std::nullopt
    };

    return 
        GameBoard::create(105, 123, board_callbacks)
        .rightFlatMap([&](auto&& board_ptr) {
            return GameBuyMenu::create(263, 135, font, buy_callbacks)
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
}

void GameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    board->render_board(event);
    buy_menu->render_selector();
}

void GameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}

void GameScene::on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}