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
    std::optional<Coordinate> selected_field;

    std::unique_ptr<GameBoard> board;
    std::unique_ptr<GameBuyMenu> buy_menu;
    std::unique_ptr<GameUpgradeMenu> upgrade_menu;

    GameStatusText points_text;
    GameStatusText gold_text;
    GameStatusBar status_bar;
    GameTooltipBox tooltip_box;

    bool menu_shown;
    GameMenuButton menu_pause_button;
    GameMenuButton menu_resume_button;
    GameMenuButton menu_save_button;
    GameMenuButton menu_options_button;
    GameMenuButton menu_exit_button;
    std::optional<std::string> clicked_scene;

    GameModel& model;
    
    std::shared_ptr<ALLEGRO_FONT> huge_font_ptr;

    GameScene(
        GameModel& _model, std::unique_ptr<GameBoard>&& _board,
        std::unique_ptr<GameBuyMenu>&& _buy_menu, std::unique_ptr<GameUpgradeMenu> _upgrade_menu,
        GameStatusText&& points_text, GameStatusText&& gold_text, GameStatusBar&& status_bar,
        GameTooltipBox&& tooltip_box, std::shared_ptr<ALLEGRO_FONT> huge_font_ptr
    );
public:
    static neither::Either<std::string, std::unique_ptr<GameScene>> create(GameModel& model);

    void set_selected_field(std::optional<Coordinate> pos);

    void render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
    void on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
    void on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;

    void on_scene_enter(std::string previous_scene) override;
};