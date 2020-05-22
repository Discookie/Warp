#pragma once

#include <neither/either.hpp>

#include "../scene/scene.h"
#include "elements/menu_button.h"
#include "elements/menu_image.h"
#include "elements/menu_text.h"

struct CreditsFonts {
    std::shared_ptr<ALLEGRO_FONT> default_font;
    std::shared_ptr<ALLEGRO_FONT> small_font;
    std::shared_ptr<ALLEGRO_FONT> big_font;
    std::shared_ptr<ALLEGRO_FONT> bold_font;
};

class CreditsScene : public Scene {
private:
    MenuImage header_image;
    CreditsFonts fonts;

    MenuButton back_button;
    
    std::optional<std::string> clicked_scene;

    CreditsScene(MenuImage &&img, CreditsFonts &&fonts);

public:
    static neither::Either<std::string, std::unique_ptr<CreditsScene>> create();

    void render_scene(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;

    void on_mouse_event(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override;
};