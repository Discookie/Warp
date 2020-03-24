#pragma once

#include <unordered_map>
#include <memory>
#include <optional>

#include "scene.h"
#include "scene_messenger.h"

class SceneManager {
    // Note: Allows for 'uninitialized' scenes
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;

    /// Stores a reference to the current scene, or nullopt if the current scene is '' or 'exit'
    std::optional<std::reference_wrapper<
        std::pair<const std::string, std::unique_ptr<Scene>>
    >> current_scene;
public:
    SceneManager();

    /// Note: The scene names '' and 'exit' are reserved
    void add_scene(std::string name, std::unique_ptr<Scene>&& scene, bool replace_existing = true);
    /// If the current scene is removed, the current scene becomes ''
    std::optional<std::unique_ptr<Scene>> remove_scene(std::string scene);

    /// On invalid scene, sets the scene to ''.
    void set_scene(std::string scene);
    bool is_exited() const { return !current_scene; }

    /// Handles the entire render cycle, from clearing the display to flipping.
    void render(const ALLEGRO_EVENT& event);
    /// Note: Does not accept render timer events.
    void handle_event(const ALLEGRO_EVENT& event);
};