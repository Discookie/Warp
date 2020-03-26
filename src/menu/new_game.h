#pragma once

#include <neither/either.hpp>

#include "../scene/scene.h"
#include "elements/menu_difficulty.h"
#include "elements/menu_button.h"
#include "elements/menu_image.h"

class NewGameScene : public Scene {
private:
    MenuImage header_image;
    std::unique_ptr<MenuDifficulty> diff;

    MenuButton start_button;
    MenuButton back_button;
    std::optional<std::string> clicked_scene;

    NewGameScene(std::unique_ptr<MenuDifficulty>&& difficulty, std::shared_ptr<ALLEGRO_FONT> font, MenuImage image);
public:
    /// unique_ptr guarantees that the lambdas used for the buttons always stay valid.
    static neither::Either<std::string, std::unique_ptr<NewGameScene>> create(std::optional<std::function<void(int)>> onDiffChange);

    void render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
    void on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) override;
};