#pragma once

#include <allegro5/allegro_image.h>

#include <memory>
#include <neither/either.hpp>
#include <string>

#include "../../utils/deleters.hpp"

class MenuImage {
private:
    int x, y;
    std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter> image;

public:
    MenuImage() = default;

    MenuImage(int center_x, int center_y, std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter> &&img)
        : x(center_x),
          y(center_y),
          image(std::move(img)) {}

    static neither::Either<std::string, MenuImage> load_from_path(
        int center_x, int center_y, const std::string &path);

    void render_image() const;
};