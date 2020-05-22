#include "credits.h"

#include <allegro5/allegro_ttf.h>

#include <functional>
#include <memory>
#include <optional>
#include <tuple>

const int MENU_WIDTH = 200;
using font_ptr       = std::shared_ptr<ALLEGRO_FONT>;
using scene_ptr      = std::unique_ptr<CreditsScene>;

neither::Either<std::string, std::unique_ptr<CreditsScene>> CreditsScene::create() {
    // 200px x 70px
    return MenuImage::load_from_path(160, 45, "assets/header.png")
        .rightFlatMap([](auto&& img) {
            using ret_ty = neither::Either<std::string, std::tuple<MenuImage, CreditsFonts>>;

            font_ptr font = font_ptr(al_create_builtin_font(), FontDeleter());
            font_ptr small_font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -10, 0), FontDeleter());
            font_ptr big_font = font_ptr(al_load_ttf_font("assets/slkscr.ttf", -20, 0), FontDeleter());
            font_ptr bold_font = font_ptr(al_load_ttf_font("assets/slkscrb.ttf", -20, 0), FontDeleter());

            if (!font || !small_font || !big_font || !bold_font) {
                return ret_ty::leftOf("failed to load font");
            } else {
                return ret_ty::rightOf(std::make_tuple(
                    std::forward<decltype(img)>(img),
                    CreditsFonts{font, small_font, big_font, bold_font}
                ));
            }
        })
        .rightMap([](auto&& tuple_img_fonts) {
            return std::unique_ptr<CreditsScene>(
                new CreditsScene(  // NOLINT(modernize-make-unique)
                    std::move(std::get<0>(tuple_img_fonts)), std::move(std::get<1>(tuple_img_fonts))));
        });
}

CreditsScene::CreditsScene(MenuImage &&img, CreditsFonts&& _fonts)
 : fonts(std::move(_fonts))
{
    header_image = std::move(img);
        
    back_button = MenuButton(
        110, 220, 95, 20, "Back", fonts.default_font,
        [&](){ clicked_scene = "main_menu"; }
    );


    clicked_scene = std::nullopt;
}

void CreditsScene::render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    header_image.render_image();
    
    al_draw_text(fonts.small_font.get(), al_map_rgb(155, 227, 157),
        30, 80, ALLEGRO_ALIGN_LEFT, "Developers");
    
    al_draw_text(fonts.small_font.get(), al_map_rgb(255, 255, 255),
        145, 95, ALLEGRO_ALIGN_RIGHT, "Game logic, QA");
    al_draw_text(fonts.small_font.get(), al_map_rgb(255, 255, 255),
        145, 110, ALLEGRO_ALIGN_RIGHT, "Backend, Infra");
    al_draw_text(fonts.small_font.get(), al_map_rgb(255, 255, 255),
        145, 125, ALLEGRO_ALIGN_RIGHT, "Graphics, UX");

    al_draw_text(fonts.big_font.get(), al_map_rgb(255, 255, 255),
        155, 87, ALLEGRO_ALIGN_LEFT, "Baffy Benjamin");
    al_draw_text(fonts.big_font.get(), al_map_rgb(255, 255, 255),
        155, 104, ALLEGRO_ALIGN_LEFT, "Discookie");
    al_draw_text(fonts.big_font.get(), al_map_rgb(255, 255, 255),
        155, 122, ALLEGRO_ALIGN_LEFT, "Poór Boldizsár");

    al_draw_text(fonts.small_font.get(), al_map_rgb(155, 227, 157),
        30, 140, ALLEGRO_ALIGN_LEFT, "Libraries");

    al_draw_text(fonts.small_font.get(), al_map_rgb(255, 255, 255),
        145, 155, ALLEGRO_ALIGN_RIGHT, "Graphics framework");
    al_draw_text(fonts.small_font.get(), al_map_rgb(255, 255, 255),
        145, 170, ALLEGRO_ALIGN_RIGHT, "Font");

    al_draw_text(fonts.big_font.get(), al_map_rgb(255, 255, 255),
        155, 148, ALLEGRO_ALIGN_LEFT, "Allegro");
    al_draw_text(fonts.big_font.get(), al_map_rgb(255, 255, 255),
        155, 165, ALLEGRO_ALIGN_LEFT, "Silkscreen");

    al_draw_text(fonts.bold_font.get(), al_map_rgb(204, 127, 118),
        165, 185, ALLEGRO_ALIGN_CENTER, "Thank you for playing!");

    back_button.render_button();
}

void CreditsScene::on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        back_button.on_click(event.mouse);

        if (clicked_scene) {
            messenger.switch_scene(*clicked_scene);
            clicked_scene = std::nullopt;
        }
    }
}