#include "options.h"

#include <functional>
#include <memory>
#include <optional>
#include <tuple>

const int MENU_WIDTH = 200;
using font_ptr       = std::shared_ptr<ALLEGRO_FONT>;
using scene_ptr      = std::unique_ptr<OptionsScene>;

neither::Either<std::string, std::unique_ptr<OptionsScene>> OptionsScene::create(
    std::function<int()>&& scale_getter, std::function<void(bool)>&& scale_setter
) {
    // 200px x 70px
    return MenuImage::load_from_path(160, 45, "assets/header.png")
        .rightFlatMap([](auto&& img) {
            using ret_ty = neither::Either<std::string, std::tuple<MenuImage, font_ptr>>;

            font_ptr font = font_ptr(al_create_builtin_font(), FontDeleter());

            if (!font) {
                return ret_ty::leftOf("failed to load font");
            } else {
                return ret_ty::rightOf(std::make_tuple(std::forward<decltype(img)>(img), font));
            }
        })
        .rightMap([&scale_getter, &scale_setter](auto&& tuple_img_font) {
            return std::unique_ptr<OptionsScene>(
                new OptionsScene(  // NOLINT(modernize-make-unique)
                    std::move(std::get<0>(tuple_img_font)), std::get<1>(tuple_img_font),
                    std::move(scale_getter), std::move(scale_setter)));
        });
}

OptionsScene::OptionsScene(
    MenuImage &&img, const std::shared_ptr<ALLEGRO_FONT> &font,
    std::function<int()>&& _scale_getter, std::function<void(bool)>&& _scale_setter
) : scale_getter(_scale_getter), scale_setter(_scale_setter) {
    header_image = std::move(img);

    scale_text = MenuText(160, 120, "Scale: " + std::to_string(scale_getter()), font);
    scale_minus_button = MenuButton(
        100, 120, 30, 20, "-", font,
        [&]() { 
            scale_setter(false);
            scale_text.set_text("Scale: " + std::to_string(scale_getter()));
        }
    );
    scale_plus_button = MenuButton(
        220, 120, 30, 20, "+", font,
        [&]() {
            scale_setter(true);
            scale_text.set_text("Scale: " + std::to_string(scale_getter()));
        }
    );
        
    back_button = MenuButton(
        110, 220, 95, 20, "Back", font,
        [&](){ clicked_scene = "main_menu"; }
    );


    clicked_scene = std::nullopt;
}

void OptionsScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    header_image.render_image();

    scale_text.render_text();
    scale_minus_button.render_button();
    scale_plus_button.render_button();

    back_button.render_button();
}

void OptionsScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        scale_minus_button.on_click(event.mouse);
        scale_plus_button.on_click(event.mouse);
        back_button.on_click(event.mouse);

        if (clicked_scene) {
            messenger.switch_scene(*clicked_scene);
            clicked_scene = std::nullopt;
        }
    }
}