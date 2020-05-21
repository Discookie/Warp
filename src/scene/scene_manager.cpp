#include "scene_manager.h"

using scene_ptr    = std::unique_ptr<Scene>;
using hashmap_elem = std::pair<const std::string, std::unique_ptr<Scene>>;

SceneManager::SceneManager() : scenes(), current_scene() {
    scenes.insert({"exit", std::move(scene_ptr(nullptr))});
}

void SceneManager::add_scene(const std::string &name, scene_ptr &&scene, bool replace_existing) {
    if (name.empty() || name == "exit") {
        return;
    }

    // The reference may be invalidated on insertion, better be safe and
    // re-initialize it
    std::string current_scene_name = (current_scene) ? current_scene->get().first : "";

    if (replace_existing) {
        scenes.insert_or_assign(name, std::move(scene));
    } else {
        scenes.insert({name, std::move(scene)});
    }

    set_scene(current_scene_name);
}

std::optional<scene_ptr> SceneManager::remove_scene(const std::string &scene) {
    if (current_scene && current_scene->get().first == scene) {
        current_scene = std::nullopt;
    }

    auto removed_scene = scenes.extract(scene);

    if (removed_scene) {
        return std::move(removed_scene.mapped());
    }

    return std::nullopt;
}

void SceneManager::set_scene(const std::string &scene_name) {
    std::string old_scene;
    if (current_scene) {
        scene_ptr &scene = current_scene->get().second;
        if (scene) { scene->on_scene_leave(scene_name); }
        old_scene = current_scene->get().first;
    }

    if (scene_name.empty() || scene_name == "exit") {
        current_scene = std::nullopt;
    } else {
        auto found_scene = scenes.find(scene_name);

        if (found_scene == scenes.end()) {
            current_scene = std::nullopt;
        } else {
            current_scene = *found_scene;
            found_scene->second->on_scene_enter(old_scene);
        }
    }
}

void SceneManager::render(const ALLEGRO_EVENT &event) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (!current_scene) {
        al_flip_display();
        return;
    }

    SceneMessenger messenger = SceneMessenger();

    scene_ptr &scene = current_scene->get().second;

    if (scene) {
        scene->render_scene(messenger, event);

        if (messenger.get_scene()) {
            set_scene(*messenger.get_scene());

            scene_ptr &new_scene = current_scene->get().second;
        }
    }

    al_flip_display();
}

void SceneManager::handle_event(const ALLEGRO_EVENT &event) {
    if (!current_scene) {
        return;
    }

    scene_ptr &scene         = current_scene->get().second;
    SceneMessenger messenger = SceneMessenger();

    switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_KEY_CHAR:
            scene->on_keyboard_event(messenger, event);
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        case ALLEGRO_EVENT_MOUSE_WARPED:
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
            scene->on_mouse_event(messenger, event);
            break;

        default:
            scene->on_event(messenger, event);
            break;
    }

    // window is closed
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        messenger.switch_scene("exit");
    }

    if (messenger.get_scene()) {
        set_scene(*messenger.get_scene());
    }
}