#include "menu_difficulty.h"

#include <allegro5/allegro_primitives.h>
#include <iostream>

using fn_opt = std::optional<std::function<void(int)>>;

void MenuDifficultyButton::render_button(bool is_active) {
    int font_height = al_get_font_line_height(font.get());


    al_draw_rectangle(
        // Border is added onto the outside
        x - (w-1)/2, y - (h-1)/2,
        x + w/2,     y + h/2,
        al_map_rgb(175, 175, 175), 1
    );
    image.render_image();
    al_draw_text(
        font.get(), al_map_rgb(255, 255, 255),
        x, y + (h+1)/2 - font_height * 3/2,
        ALLEGRO_ALIGN_CENTRE, text.c_str()
    );

    if (is_active) {
        al_draw_rectangle(
            // 3px of border only adds 2px of width towards the inside
            x - 2 - (w-1)/2, y - 2 - (h-1)/2,
            x + 2 + w/2,     y + 2 + h/2,
            al_map_rgb(106, 193, 200), 3
        );
    }
}

void MenuDifficultyButton::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    auto is_between = [](int num, int bot, int top) {
        return num >= bot && num <= top;
    };

    if (is_between(event.x, x - w/2, x + (w+1)/2)
     && is_between(event.y, y - h/2, y + (h+1)/2)
    ) {
        if (callback) {
            (*callback) ();
        }
    }
}


neither::Either<std::string, std::unique_ptr<MenuDifficulty>> MenuDifficulty::create(int centerY, std::shared_ptr<ALLEGRO_FONT> buttonFont, fn_opt onDiffChanged) {
    using diff_ptr = std::unique_ptr<MenuDifficulty>;

    std::vector<MenuDifficultyButton> buttons;

    const int easy_x = 55;
    const int normal_x = 160;
    const int hard_x = 265;

    return MenuImage::load_from_path(easy_x, centerY, "assets/easy_diff.png")
        .rightFlatMap([&](auto&& ez_img){
            buttons.push_back(MenuDifficultyButton(
                easy_x, centerY, 90, 90,
                std::move(ez_img),
                "Easy", buttonFont,
                std::nullopt
            ));

            return MenuImage::load_from_path(normal_x, centerY, "assets/normal_diff.png");
        }).rightFlatMap([&](auto&& normal_img){
            buttons.push_back(MenuDifficultyButton(
                normal_x, centerY, 90, 90,
                std::move(normal_img),
                "Normal", buttonFont,
                std::nullopt
            ));

            return MenuImage::load_from_path(hard_x, centerY, "assets/hard_diff.png");
        }).rightMap([&](auto&& hard_img){
            buttons.push_back(MenuDifficultyButton(
                hard_x, centerY, 90, 90,
                std::move(hard_img),
                "Hard", buttonFont,
                std::nullopt
            ));

            return std::make_unique<MenuDifficulty>(std::move(buttons), onDiffChanged);
        });
}


MenuDifficulty::MenuDifficulty(std::vector<MenuDifficultyButton>&& difficulties, fn_opt onDiffChanged) 
  : diffs(std::move(difficulties)),
    selected_diff(difficulties.size()/2),
    callback(onDiffChanged)
{
    int idx = 0;
    for (auto& diff : diffs) {
        diff.set_callback([&, idx](){
            selected_diff = idx;
        });

        idx++;
    }
};

void MenuDifficulty::set_difficulty(int difficulty) {
    if (difficulty >= 0 && difficulty < diffs.size()) {
        selected_diff = difficulty;
    }
}

void MenuDifficulty::on_click(const ALLEGRO_MOUSE_EVENT& event) {
    for (auto& diff : diffs) {
        diff.on_click(event);
    }
}

void MenuDifficulty::on_key_down(const ALLEGRO_KEYBOARD_EVENT& event) {
    switch (event.keycode) {
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
            selected_diff = selected_diff - 1 >= 0 ? selected_diff - 1 : diffs.size() - 1;
            break;

        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
            selected_diff = selected_diff + 1 < diffs.size() ? selected_diff + 1 : 0;
            break;
    }
}

void MenuDifficulty::render_selector() {
    int idx = 0;

    for (auto& diff : diffs) {
        diff.render_button(idx == selected_diff);
        idx++;
    }
}