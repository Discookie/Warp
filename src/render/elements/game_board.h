#pragma once

#include "game_sprite.h"
#include "../../model/GameModel.h"

struct GameBoardCallbacks {
    /// Returns whether the board should mark the field as selected.
    std::optional<std::function<bool(Coordinate)>> on_select_field;
    std::optional<std::function<void(Coordinate)>> on_drag_end;
    std::function<const Field&(Coordinate)> get_field;
};

class GameBoard {
    std::vector<std::optional<GameSprite>> sprites;
    int x, y;
    std::optional<Coordinate> selected_field;

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
    
    GameBoardCallbacks& modify_callbacks() { return callbacks; }
    void clear_selection() { selected_field = std::nullopt; }
    std::optional<Coordinate> get_selected_field() { return selected_field; }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void on_release(const ALLEGRO_MOUSE_EVENT& event);
    void render_board(const ALLEGRO_EVENT& event);
};