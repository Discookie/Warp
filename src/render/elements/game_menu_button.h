#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <functional>
#include <memory>
#include <optional>
#include <utility>

class GameMenuButton {
private:
    int x, y, w, h;
    bool enabled;
    std::string text;
    std::shared_ptr<ALLEGRO_FONT> font;
    std::optional<std::function<void()>> callback;

public:
    GameMenuButton() = default;

    GameMenuButton(
        int center_x, int center_y, int width, int height, std::string button_text,
        std::shared_ptr<ALLEGRO_FONT> button_font, std::optional<std::function<void()>> on_click)
        : x(center_x),
          y(center_y),
          w(width),
          h(height),
          enabled(true),
          text(std::move(button_text)),
          font(std::move(button_font)),
          callback(std::move(on_click)) {}

    bool is_enabled() const { return enabled; }

    void enable() { enabled = true; }

    void disable() { enabled = false; }

    void toggle() { enabled = !enabled; }

    void set_text(std::string new_text) { text = std::move(new_text); }

    void set_callback(std::optional<std::function<void()>> on_click) {
        callback = std::move(on_click);
    }

    void on_click(const ALLEGRO_MOUSE_EVENT &event);

    void render_button() const;
};