#pragma once

#include "game_sprite.h"
#include "../../model/GameModel.h"

struct GameBoardCallbacks {
    std::function<void(Coordinate)> on_click;
    std::function<void(Coordinate)> on_drag_end;
    std::function<Field&(Coordinate)> get_field;
};

class GameBoard {
    std::vector<std::optional<GameSprite>> sprites;
    int x, y;

    GameBoardCallbacks callbacks;

    GameBoard(
        int center_x, int center_y,
        std::vector<std::optional<GameSprite>>&& sprite_list,
        GameBoardCallbacks callback_list
    ) : x(center_x), y(center_y), sprites(std::move(sprite_list)), callbacks(callback_list) {}
public:
    static neither::Either<std::string, std::unique_ptr<GameBoard>> create(
        int center_x, int center_y,
        GameBoardCallbacks callback_list
    );
    
    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_board(const ALLEGRO_EVENT& event);
};