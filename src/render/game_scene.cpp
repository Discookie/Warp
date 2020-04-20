#include "game_scene.h"

#include <functional>

using scene_ptr = std::unique_ptr<GameScene>;

neither::Either<std::string, scene_ptr> GameScene::create(GameModel& model) {
    auto board_click = [](Coordinate _c) {};
    auto board_drag_end = [](Coordinate _c) {};
    GameBoardCallbacks board_callbacks = {
            [](Coordinate _c){},
            [](Coordinate _c){},
            std::bind(&GameModel::get_field, model, std::placeholders::_1)
        };

    return 
        GameBoard::create(105, 123, board_callbacks)
        .rightMap([&model](auto&& board) {
            return scene_ptr(new GameScene(model, std::move(board)));
        });
}

void GameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    board.render_board(event);
}

void GameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}

void GameScene::on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}