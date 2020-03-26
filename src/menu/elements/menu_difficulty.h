#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "menu_image.h"

class MenuDifficultyButton {
private:
    int x, y, w, h;
    MenuImage image;
    std::string text;
    std::shared_ptr<ALLEGRO_FONT> font;
    std::optional<std::function<void()>> callback;
public:
    MenuDifficultyButton() = default;
    MenuDifficultyButton(int centerX, int centerY, int width, int height,
               MenuImage&& buttonImage,
               std::string buttonText, std::shared_ptr<ALLEGRO_FONT> buttonFont,
               std::optional<std::function<void()>> onClick
    ) : x(centerX), y(centerY), w(width), h(height),
        image(std::move(buttonImage)),
        text(buttonText), font(buttonFont),
        callback(onClick) {}

    void set_text(std::string newText) { text = newText; }
    void set_callback(std::optional<std::function<void()>> onClick) { callback = onClick; }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void render_button(bool is_active = false);
};


class MenuDifficulty {
    std::vector<MenuDifficultyButton> diffs;
    int selected_diff;

    std::optional<std::function<void(int)>> callback;

public:
    MenuDifficulty() = default;
    MenuDifficulty(std::vector<MenuDifficultyButton>&& difficulties, std::optional<std::function<void(int)>> onDiffChanged);

    static neither::Either<std::string, std::unique_ptr<MenuDifficulty>> create(int centerY, std::shared_ptr<ALLEGRO_FONT> buttonFont, std::optional<std::function<void(int)>> onDiffChanged);

    void set_difficulty(int difficulty);
    int selected_difficulty() { return selected_diff; }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void on_key_down(const ALLEGRO_KEYBOARD_EVENT& event);
    void render_selector();
};