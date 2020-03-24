#include <functional>
#include <optional>
#include <tuple>

#include "main_menu.h"

const int MENU_WIDTH = 200;
using font_ptr = std::shared_ptr<ALLEGRO_FONT>;
using scene_ptr = std::unique_ptr<MainMenuScene>;

neither::Either<std::string, std::unique_ptr<MainMenuScene>> MainMenuScene::create() {

    // 200px x 70px
    return MenuImage::load_from_path(160, 45, "assets/header.png")
        .rightFlatMap( [](auto&& img) {
            using ret_ty = neither::Either<std::string, std::tuple<MenuImage, font_ptr>>;

            font_ptr font = font_ptr(al_create_builtin_font(), FontDeleter());

            if (!font) {
                return ret_ty::leftOf("failed to load font");
            } else {
                return ret_ty::rightOf(std::make_tuple(std::move(img), font));
            }
        }).rightMap( [](auto&& tuple_img_font) {
            return std::unique_ptr<MainMenuScene>(new MainMenuScene(
                std::move(std::get<0>(tuple_img_font)),
                std::get<1>(tuple_img_font)
            ));
        });
}

MainMenuScene::MainMenuScene(MenuImage&& img, font_ptr font) {
    header_image = std::move(img);
    
    new_game_button = MenuButton(
        160, 100, MENU_WIDTH, 20,
        "New game", font,
        [&](){ clicked_scene = "new_game"; }
    );
    new_game_button.disable();
    load_game_button = MenuButton(
        160, 130,
        MENU_WIDTH, 20,
        "Load game", font,
        [&](){ clicked_scene = "load_game"; }
    );
    load_game_button.disable();
    options_button = MenuButton(
        160, 160,
        MENU_WIDTH, 20,
        "Options", font,
        [&](){ clicked_scene = "options"; }
    );
    options_button.disable();
    credits_button = MenuButton(
        160, 190,
        MENU_WIDTH, 20,
        "Credits", font,
        [&](){ clicked_scene = "credits"; }
    );
    credits_button.disable();
    exit_button = MenuButton(
        160, 225,
        MENU_WIDTH, 20,
        "Exit", font,
        [&](){ clicked_scene = "exit"; }
    );

    clicked_scene = std::nullopt;
}

void MainMenuScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    header_image.render_image();

    new_game_button.render_button();
    load_game_button.render_button();
    options_button.render_button();
    credits_button.render_button();
    exit_button.render_button();
}

void MainMenuScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        new_game_button.on_click(event.mouse);
        load_game_button.on_click(event.mouse);
        options_button.on_click(event.mouse);
        credits_button.on_click(event.mouse);
        exit_button.on_click(event.mouse);

        if (clicked_scene) {
            messenger.switch_scene(*clicked_scene);
            clicked_scene = std::nullopt;
        }
    }
}