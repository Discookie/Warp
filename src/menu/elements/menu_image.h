#pragma once

#include <memory>
#include <string>

#include <allegro5/allegro_image.h>
#include <neither/either.hpp>

#include "../../utils/deleters.hpp"

class MenuImage {
private:
    int x, y;
    std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter> image;
public:
    MenuImage() = default;
    MenuImage(int centerX, int centerY, std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter>&& img)
        : x(centerX), y(centerY), image(std::move(img)) {}
        
    static neither::Either<std::string, MenuImage> load_from_path(int centerX, int centerY, std::string path);

    void render_image() const;
};