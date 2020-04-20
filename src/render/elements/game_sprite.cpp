#include "game_sprite.h"

neither::Either<std::string, GameSprite> GameSprite::create(const std::string& sprite_name) {
    using uptr = std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter>;
    using retTy = neither::Either<std::string, GameSprite>;

    std::string small_path = "assets/" + sprite_name + "_small.png";
    
    uptr small_sprite = uptr(al_load_bitmap(small_path.c_str()));

    if (!small_sprite) {
        return retTy::leftOf("failed to load sprite '" + sprite_name + "_small'");
    }

    GameSprite ret = GameSprite(std::move(small_sprite));
    return retTy::rightOf(std::move(ret));
}

void GameSprite::render_sprite_16px(int left, int top, const ALLEGRO_EVENT& event) const {
    ALLEGRO_BITMAP* raw_image = small_sprite.get();
    al_draw_bitmap(
        raw_image,
        left,
        top,
        0
    );
}