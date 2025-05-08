#include "gui/modules/submenu.h"
#include "gui/view_dispatcher.h"
#include "gui/scene_manager.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_gpio_list_menu_callback(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "la_gpio_list_menu_callback");
    LAApp* app = context;
    scene_manager_handle_custom_event(app->scene_manager, index);
}

void la_scene_gpio_list_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_enter");
    LAApp* app = context;
    submenu_reset(app->gpio_list);

    // add menu entries
    for(int i = 0; i < 10; i++) {
        // Generate label
        char* str = (char*)malloc(20 * sizeof(char));
        str[0] = '\0';
        char num_str[10];
        la_int_to_str(i, num_str);
        la_concat(str, num_str);
        la_concat(str, ". Element");

        submenu_add_item(app->gpio_list, str, i, la_gpio_list_menu_callback, app);
    }

    view_dispatcher_switch_to_view(app->view_dispatcher, LA_Menu);
}

void la_scene_gpio_list_on_exit(void* context) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_exit");
    LAApp* app = context;
    submenu_reset(app->gpio_list);
}

bool la_scene_gpio_list_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_event");
    LAApp* app = context;
    bool consumed = false;
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) { // handle custom event, event.event is the id in the menu
        default:
            scene_manager_next_scene(app->scene_manager, LaSceneGpioList);
            consumed = true;
            break;
        }
    }
    return consumed;
}
