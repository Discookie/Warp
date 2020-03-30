#include "menu_image.h"

neither::Either<std::string, MenuImage> MenuImage::load_from_path(
    int center_x, int center_y, const std::string &path) {
    using uptr   = std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter>;
    using ret_ty = neither::Either<std::string, MenuImage>;
    uptr image   = uptr(al_load_bitmap(path.c_str()));

    if (!image) {
        return ret_ty::leftOf("failed to load image '" + path + "'");
    }

    MenuImage ret = MenuImage(center_x, center_y, std::move(image));
    return ret_ty::rightOf(std::move(ret));
}

void MenuImage::render_image() const {
    ALLEGRO_BITMAP *raw_image = image.get();
    al_draw_bitmap(
        raw_image, x - al_get_bitmap_width(raw_image) / 2, y - al_get_bitmap_height(raw_image) / 2,
        0);
}