#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class MenuButton {
private:
    int x, y, w, h;
    bool enabled;
    std::string text;
    std::shared_ptr<ALLEGRO_FONT> font;
    std::optional<std::function<void()>> callback;
public:
    MenuButton() = default;
    MenuButton(int centerX, int centerY, int width, int height,
               std::string buttonText, std::shared_ptr<ALLEGRO_FONT> buttonFont,
               std::optional<std::function<void()>> onClick
    ) : x(centerX), y(centerY), w(width), h(height), enabled(true),
        text(buttonText), font(buttonFont),
        callback(onClick) {}

    bool is_enabled() const { return enabled; }
    void enable() { enabled = true; }
    void disable() { enabled = false; }
    void toggle() { enabled = !enabled; }
    
    void set_text(std::string newText) { text = newText; }
    void set_callback(std::optional<std::function<void()>> onClick) { callback = onClick; }

    void on_click(const ALLEGRO_MOUSE_EVENT& event);
    void render_button() const;
};