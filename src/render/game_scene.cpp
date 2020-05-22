#include "game_scene.h"
#include "../model/Constants.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <functional>

using scene_ptr = std::unique_ptr<GameScene>;
using font_ptr = std::shared_ptr<ALLEGRO_FONT>;

neither::Either<std::string, scene_ptr> GameScene::create(GameModel& model) {
    font_ptr font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -10, 0), FontDeleter());
    font_ptr huge_font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -40, 0), FontDeleter());

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

    GameStatusText points_text = GameStatusText(105, 14, 70, "Points:", "", font);
    GameStatusText gold_text = GameStatusText(182, 14, 70, "Gold:", "", font);
    GameStatusBar status_bar = GameStatusBar(283, 14, 70, 0, "Wave:", font);
    GameTooltipBox tooltip_box = GameTooltipBox(124, 233, 224, 12, font);

    return 
        GameBoard::create(124, 128, board_callbacks)
        .rightFlatMap([&](auto&& board_ptr) {
            return GameBuyMenu::create(283, 116, font, buy_callbacks)
                .rightMap([&board_ptr](auto&& buymenu_ptr) {
                    return std::make_tuple(std::move(board_ptr), std::move(buymenu_ptr));
                });
        }).rightFlatMap([&](auto&& tuple_board_buymenu) {
            return GameUpgradeMenu::create(283, 210, font, upgrade_callbacks)
                .rightMap([&tuple_board_buymenu](auto&& upgrade_ptr) {
                    auto&& board = std::get<0>(tuple_board_buymenu);
                    auto&& buymenu = std::get<1>(tuple_board_buymenu);
                    return std::make_tuple(std::move(board), std::move(buymenu), std::move(upgrade_ptr));
                });
        }).rightMap([&](auto&& tuple_board_buymenu_upgrade) {
            auto&& board = std::get<0>(tuple_board_buymenu_upgrade);
            auto&& buymenu = std::get<1>(tuple_board_buymenu_upgrade);
            auto&& upgrade = std::get<2>(tuple_board_buymenu_upgrade);
            return scene_ptr(new GameScene(
                model, std::move(board),
                std::move(buymenu), std::move(upgrade),
                std::move(points_text), std::move(gold_text),
                std::move(status_bar), std::move(tooltip_box),
                huge_font
            ));
        });
}

GameScene::GameScene(
    GameModel& _model, std::unique_ptr<GameBoard>&& _board,
    std::unique_ptr<GameBuyMenu>&& _buy_menu, std::unique_ptr<GameUpgradeMenu> _upgrade_menu,
    GameStatusText&& _points_text, GameStatusText&& _gold_text,
    GameStatusBar&& _status_bar, GameTooltipBox&& _tooltip_box,
    std::shared_ptr<ALLEGRO_FONT> _huge_font_ptr
) : model(_model), board(std::move(_board)), selected_field(std::nullopt),
    buy_menu(std::move(_buy_menu)), upgrade_menu(std::move(_upgrade_menu)),
    gold_text(_gold_text), points_text(_points_text), status_bar(_status_bar),
    menu_shown(false), clicked_scene(std::nullopt), tooltip_box(_tooltip_box),
    huge_font_ptr(_huge_font_ptr)
{
    GameBoardCallbacks& board_callbacks = board->modify_callbacks();
    
    board_callbacks.on_select_field = [&](Coordinate pos) {
        bool building_tower = buy_menu->get_selected_item() >= 0;

        if (building_tower) {
            auto result = model.add_friendly_entity(pos);
            if (result) {
                tooltip_box.show_text(*result);
                return !building_tower;
            }

            buy_menu->clear_selection();
            set_selected_field(std::nullopt);
        } else if (selected_field) {
            set_selected_field(std::nullopt);
        } else {
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
            auto result = model.upgrade_tower(*selected_field);
            if (result) {
                tooltip_box.show_text(*result);
                return;
            }

            upgrade_menu->set_upgrade_visible(false); // FIXME: Check manually for upgraded state here
            // do not clear field here
        }
    };
    upgrade_callbacks.on_delete = [&]() {
        if (selected_field) {
            auto result = model.remove_tower(*selected_field);
            if (result) {
                tooltip_box.show_text(*result);
                return;
            }

            set_selected_field(std::nullopt);
        }
    };

    font_ptr font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -10, 0), FontDeleter());
    menu_pause_button = GameMenuButton(35, 14, 56, 15, "Pause", font, [&]() { menu_shown = true; });
    font_ptr menu_font = font_ptr(al_create_builtin_font(), FontDeleter());
    
    // Moved up for reference reasons
    menu_exit_button = GameMenuButton(135, 200, 200, 20, "Exit without saving", menu_font, [&]() {
        clicked_scene = "main_menu";
    });

    menu_resume_button = GameMenuButton(135, 70, 200, 20, "Resume", menu_font, [&]() {
        menu_shown = false;
        menu_exit_button.set_text("Exit without saving");
    });
    menu_save_button = GameMenuButton(135, 120, 200, 20, "Save", menu_font, [&]() {
        model.save_game();
        menu_exit_button.set_text("Exit");
    });
    menu_options_button = GameMenuButton(135, 150, 200, 20, "Options", menu_font, [&]() { 
        clicked_scene = "options";
    });
}

void GameScene::set_selected_field(std::optional<Coordinate> pos) {
    std::shared_ptr<const Stable> tower;
    EntityType tower_type = EntityType::TypeNone;
    bool is_upgraded = false;
    
    if (pos 
        && (tower = model.get_field_const(*pos).get_tower_const())
        && (tower_type = tower->get_entity_type()) != EntityType::TypeNone
    ) {
        is_upgraded = tower->is_upgraded();
    } else {
        pos = std::nullopt;
    }

    upgrade_menu->set_prices(tower_type, is_upgraded);
    selected_field = pos;
}

void GameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // Tick the model
    // FIXME: Move this to a better location
    // FIXME: Reset the model on scene leave/enter
    // TODO: Track previous frame for frameskips
    if (!menu_shown && !model.is_game_over()) {
        model.update();
        
        if (!model.is_game_over()) {
            buy_menu->update_buyable(model.get_gold());
            upgrade_menu->update_buyable(model.get_gold());

                points_text.set_value(std::to_string(model.get_points()));
            gold_text.set_value(std::to_string(model.get_gold()));

                status_bar.set_fill(std::max(
                (Constants::WAVE_COUNTDOWN_TIME - model.get_wave_progress()) 
                    * 100 / Constants::WAVE_COUNTDOWN_TIME,
                0
            ));
            status_bar.set_label("Wave: " + std::to_string(model.get_wave_number()));
        }
    }
    
    // render game over backdrops under everything
    if (model.is_game_over()) {
        if (model.is_game_won()) {
            al_draw_filled_rectangle(3, 27, 23, 227, al_map_rgba(155, 227, 157, 24));
            al_draw_filled_rectangle(24, 27, 243, 227, al_map_rgba(92, 173, 95, 16));
        } else {
            al_draw_filled_rectangle(3, 27, 23, 227, al_map_rgba(204, 127, 118, 192));
            al_draw_filled_rectangle(24, 27, 243, 227, al_map_rgba(161, 77, 67, 128));
        }
    }

    board->render_board(event);
    buy_menu->render_selector();
    upgrade_menu->render_selector();

    points_text.render_text();
    gold_text.render_text();
    status_bar.render_status_bar();
    tooltip_box.render_tooltip();

    menu_pause_button.render_button();
    
    // render game over text over everything
    if (model.is_game_over()) {
        if (model.is_game_won()) {
            al_draw_text(
                huge_font_ptr.get(), al_map_rgb(255, 255, 255), 124, 88,
                ALLEGRO_ALIGN_CENTER, "CONGRATS"
            );
            al_draw_text(
                huge_font_ptr.get(), al_map_rgb(255, 255, 255), 124, 128,
                ALLEGRO_ALIGN_CENTER, "YOU WON!"
            );
        } else {
            al_draw_text(
                huge_font_ptr.get(), al_map_rgb(255, 255, 255), 124, 88,
                ALLEGRO_ALIGN_CENTER, "BETTER LUCK"
            );
            al_draw_text(
                huge_font_ptr.get(), al_map_rgb(255, 255, 255), 124, 128,
                ALLEGRO_ALIGN_CENTER, "NEXT TIME!"
            );
        }
    }

    if (menu_shown) {
        al_draw_filled_rectangle(0, 0, 320, 240, al_map_rgba(64, 64, 64, 128));
        
        menu_resume_button.render_button();
        menu_save_button.render_button();
        menu_options_button.render_button();
        menu_exit_button.render_button();
    }
}

void GameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (menu_shown) {
                menu_resume_button.on_click(event.mouse);
                menu_save_button.on_click(event.mouse);
                menu_options_button.on_click(event.mouse);
                menu_exit_button.on_click(event.mouse);

                if (clicked_scene) {
                    messenger.switch_scene(*clicked_scene);
                    clicked_scene = std::nullopt;
                }
            } else {
                if (!model.is_game_over()) {
                    board->on_click(event.mouse);
                    buy_menu->on_click(event.mouse);
                    upgrade_menu->on_click(event.mouse);
                }

                menu_pause_button.on_click(event.mouse);
            }
            break;
        
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (!menu_shown && !model.is_game_over()) {
                board->on_release(event.mouse);
                buy_menu->on_release(event.mouse);
                upgrade_menu->on_release(event.mouse);
            }
            break;

        // Mouse move
        case ALLEGRO_EVENT_MOUSE_AXES:
            break;
    }
}

void GameScene::on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    // unimplemented!();
}

void GameScene::on_scene_enter(std::string previous_scene) {
    // Check for creating new game here
    if (previous_scene == "new_game") {
        model.new_game();
    }

    // Don't unpause when returning from options scene
    if (previous_scene != "options") {
        set_selected_field(std::nullopt);
        menu_shown = false;
        menu_exit_button.set_text("Exit without saving");
    }
}