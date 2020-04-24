#pragma once

#include <memory>
#include <optional>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class MenuText {
private:
    int x, y;
    std::string text;
    std::shared_ptr<ALLEGRO_FONT> font;
public:
    MenuText() = default;
    MenuText(int centerX, int centerY,
               std::string lineText, std::shared_ptr<ALLEGRO_FONT> lineFont
    ) : x(centerX), y(centerY),
        text(lineText), font(lineFont) {}
    
    void set_text(std::string newText) { text = newText; }

    void render_text() const;
};