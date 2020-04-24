#pragma once

#include <memory>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <neither/either.hpp>

#include "../../utils/deleters.hpp"

class GameSprite {
    std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter> small_sprite;
    GameSprite(std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter>&& small) : small_sprite(std::move(small)) {}
public:
    static neither::Either<std::string, GameSprite> create(const std::string& sprite_name);
    void render_sprite_20px(int left, int top, const ALLEGRO_EVENT& event) const;
    // void render_sprite_12px(int left, int top, const ALLEGRO_EVENT& event);
};