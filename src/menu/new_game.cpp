#include <functional>
#include <optional>
#include <tuple>

#include <neither/try.hpp>

#include "new_game.h"

const int BUTTON_WIDTH = 95;
using fn_opt = std::optional<std::function<void(int)>>;
using font_ptr = std::shared_ptr<ALLEGRO_FONT>;
using scene_ptr = std::unique_ptr<NewGameScene>;

neither::Either<std::string, std::unique_ptr<NewGameScene>> NewGameScene::create(fn_opt onDiffChange) {
    font_ptr font = font_ptr(al_create_builtin_font(), FontDeleter());
    
    return MenuImage::load_from_path(160, 45, "assets/new_game.png")
        .rightFlatMap( [&font](auto&& img) {
            using ret_ty = neither::Either<std::string, std::tuple<font_ptr, MenuImage>>;

            if (!font) {
                return ret_ty::leftOf("failed to load font");
            } else {
                return ret_ty::rightOf(std::make_tuple(font, std::move(img)));
            }
        }).rightFlatMap([&onDiffChange](auto&& tuple_font_img) {
            using ret_ty = neither::Either<std::string, std::tuple<std::unique_ptr<MenuDifficulty>, font_ptr, MenuImage>>;

            auto font = std::get<0>(tuple_font_img);
            // 200px x 70px
            return MenuDifficulty::create(160, font, onDiffChange)
                .rightMap([&](auto&& diff) {
                    return std::make_tuple(
                        std::move(diff),
                        font,
                        std::move(std::get<1>(tuple_font_img))
                    );
                });
        }).rightMap( [](auto&& tuple_diff_font_img) {
            return std::unique_ptr<NewGameScene>(new NewGameScene(
                std::move(std::get<0>(tuple_diff_font_img)),
                std::get<1>(tuple_diff_font_img),
                std::move(std::get<2>(tuple_diff_font_img))
            ));
        });
}

NewGameScene::NewGameScene(std::unique_ptr<MenuDifficulty>&& difficulty, std::shared_ptr<ALLEGRO_FONT> font, MenuImage image) {
    header_image = std::move(image);
    diff = std::move(difficulty);

    start_button = MenuButton(
        210, 230,
        BUTTON_WIDTH, 20,
        "Start", font,
        [&](){ clicked_scene = "in_game"; }
    );
    start_button.disable();
    back_button = MenuButton(
        110, 230,
        BUTTON_WIDTH, 20,
        "Back", font,
        [&](){ clicked_scene = "main_menu"; }
    );

    clicked_scene = std::nullopt;
}

void NewGameScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    header_image.render_image();
    diff->render_selector();

    start_button.render_button();
    back_button.render_button();
}

void NewGameScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        diff->on_click(event.mouse);
        start_button.on_click(event.mouse);
        back_button.on_click(event.mouse);

        if (clicked_scene) {
            messenger.switch_scene(*clicked_scene);
            clicked_scene = std::nullopt;
        }
    }
}