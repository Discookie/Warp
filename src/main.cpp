#include <iostream>
#include <cstdlib>

#include <memory>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "menu/main_menu.h"
#include "scene/scene_manager.h"
#include "utils/deleters.hpp"

int main() {
    const auto not_null = [](auto ptr, std::string desc) {
        if (!ptr) {
            std::cerr << desc << " failed, exiting...";
            std::cin.get();
            std::exit(1);
        }
    };

    not_null(al_init(), "initializing allegro");
    not_null(al_install_keyboard(), "initializing keyboard");
    not_null(al_install_mouse(), "initializing mouse");
    not_null(al_init_image_addon(), "initializing image formats");
    not_null(al_init_primitives_addon(), "initializing primitives");

    std::shared_ptr<ALLEGRO_TIMER> frame_timer = std::shared_ptr<ALLEGRO_TIMER>(
        al_create_timer(1.0 / 30.0),
        [](auto* timer) { al_destroy_timer(timer); }
    );
    not_null(frame_timer, "initializing timer");

    std::shared_ptr<ALLEGRO_EVENT_QUEUE> main_queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(
        al_create_event_queue(),
        [](auto* queue) { al_destroy_event_queue(queue); }
    );
    not_null(main_queue, "initializing queue");

    std::shared_ptr<ALLEGRO_DISPLAY> display = std::shared_ptr<ALLEGRO_DISPLAY>(
        al_create_display(320, 240),
        [](auto* display) { al_destroy_display(display); }
    );
    not_null(display, "initializing display");
    
    std::shared_ptr<ALLEGRO_FONT> font = std::shared_ptr<ALLEGRO_FONT>(
        al_create_builtin_font(),
        FontDeleter()
    );
    not_null(font, "initializing default font");

    al_register_event_source(main_queue.get(), al_get_keyboard_event_source());
    al_register_event_source(main_queue.get(), al_get_mouse_event_source());
    al_register_event_source(main_queue.get(), al_get_display_event_source(display.get()));
    al_register_event_source(main_queue.get(), al_get_timer_event_source(frame_timer.get()));


    SceneManager scene_manager = SceneManager();

    auto main_menu_scene = MainMenuScene::create()
        .leftMap([&](auto&& err) {
            not_null(true, "adding main menu scene failed: " + err);
            return 0;
        }).rightMap([&](auto&& scene_ptr){
            std::unique_ptr<Scene> casted_scene_ptr = std::unique_ptr<Scene>(scene_ptr.release());
            scene_manager.add_scene("main_menu", std::move(casted_scene_ptr));
            scene_manager.set_scene("main_menu");
            return 0;
        });
    

    ALLEGRO_EVENT event;
    std::optional<ALLEGRO_EVENT> last_frame_event;

    al_start_timer(frame_timer.get());

    while(!scene_manager.is_exited()) {
        al_wait_for_event(main_queue.get(), &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            last_frame_event = event;
        } else {
            scene_manager.handle_event(event);
        }

        if(last_frame_event && al_is_event_queue_empty(main_queue.get())) {
            scene_manager.render(*last_frame_event);

            last_frame_event = std::nullopt;
        }
    }

    return 0;
}