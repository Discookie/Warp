#pragma once

#include <neither/either.hpp>

#include "../scene/scene.h"
#include "elements/menu_button.h"
#include "elements/menu_image.h"
#include "elements/menu_text.h"

class OptionsScene : public Scene {
private:
    MenuImage header_image;

    MenuButton scale_plus_button;
    MenuButton scale_minus_button;
    MenuText scale_text;
    MenuButton back_button;
    
    std::optional<std::string> clicked_scene;
    std::string previous_scene;

    std::function<int()> scale_getter;
    std::function<void(bool)> scale_setter;

    OptionsScene(
        MenuImage &&img, const std::shared_ptr<ALLEGRO_FONT> &font,
        std::function<int()>&& scale_getter, std::function<void(bool)>&& scale_setter
    );

public:
    static neither::Either<std::string, std::unique_ptr<OptionsScene>> create(
        std::function<int()>&& scale_getter, std::function<void(bool)>&& scale_setter
    );

    void render_scene(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;

    void on_mouse_event(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;

    void on_scene_enter(std::string previous_scene) override;
};