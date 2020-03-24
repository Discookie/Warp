#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class BitmapDeleter {
public:
    void operator()(ALLEGRO_BITMAP* bitmap_to_delete) {
        al_destroy_bitmap(bitmap_to_delete);
    }
};

class FontDeleter {
public:
    void operator()(ALLEGRO_FONT* font_to_delete) {
        al_destroy_font(font_to_delete);
    }
};

class TimerDeleter {
public:
    void operator()(ALLEGRO_TIMER* timer_to_delete) {
        al_destroy_timer(timer_to_delete);
    }
};