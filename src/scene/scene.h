#pragma once

#include <string>

#include <allegro5/allegro5.h>

#include "scene_messenger.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void render_scene(SceneMessenger& messenger, const ALLEGRO_EVENT& event) = 0;

    virtual void on_mouse_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {}
    virtual void on_keyboard_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {}
    virtual void on_event(SceneMessenger& messenger, const ALLEGRO_EVENT& event) {}
};