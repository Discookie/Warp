#pragma once

#include <neither/either.hpp>

#include "../scene/scene.h"
#include "elements/menu_button.h"
#include "elements/menu_image.h"

class MainMenuScene : public Scene {
private:
    MenuImage header_image;

    MenuButton new_game_button;
    MenuButton load_game_button;
    MenuButton options_button;
    MenuButton credits_button;
    MenuButton exit_button;

    std::optional<std::string> clicked_scene;

    std::function<bool()> load_game_func;

    MainMenuScene(MenuImage &&img, const std::shared_ptr<ALLEGRO_FONT> &font, std::function<bool()>&& load_game_func);

public:
    static neither::Either<std::string, std::unique_ptr<MainMenuScene>> create(std::function<bool()>&& load_game_func);

    void render_scene(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;

    void on_mouse_event(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;
};