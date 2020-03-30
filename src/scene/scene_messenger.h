#pragma once

#include <optional>

class SceneMessenger {
private:
    std::optional<std::string> new_scene;

public:
    SceneMessenger() {}

    void switch_scene(std::string scene) { new_scene = scene; }

    std::optional<std::string> get_scene() const { return new_scene; }
};