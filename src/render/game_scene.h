#pragma once

#include <allegro5/allegro5.h>
#include <neither/either.hpp>

#include "../scene/scene.h"
#include "elements/game_elements.h"

class GameScene : public Scene {
private:
    // GameButton pause_button;
    // GameStatusText points_text;
    // GameStatusText gold_text;
    // GameStatusBar wave_bar;

    std::unique_ptr<GameBoard> board;
    std::unique_ptr<GameBuyMenu> buy_menu;
    // GameUpgradeMenu upgrade_menu;

    GameModel& model;

    //std::optional<GameTooltip> tooltip;

    GameScene(GameModel& _model, std::unique_ptr<GameBoard>&& _board, std::unique_ptr<GameBuyMenu>&& _buy_menu);
public:
    static neither::Either<std::string, std::unique_ptr<GameScene>> create(GameModel& model);

    void render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
    void on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
    void on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
};