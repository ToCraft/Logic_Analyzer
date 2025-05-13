#include "gui/modules/submenu.h"
#include "gui/view_dispatcher.h"
#include "gui/scene_manager.h"
#include "la_custom_events.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_gpio_list_menu_callback_edit_con(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "la_gpio_list_menu_callback_edit_con");
    LAApp* app = context;

    UNUSED(index);
    scene_manager_handle_custom_event(app->scene_manager, LaEventGpioListEdit);
}

void la_gpio_list_menu_callback_create_con(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "la_gpio_list_menu_callback_create_con");
    LAApp* app = context;

    UNUSED(index);
    scene_manager_handle_custom_event(app->scene_manager, LaEventGpioListCreate);
}

void la_gpio_list_menu_callback_done(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "la_gpio_list_menu_callback_done");
    LAApp* app = context;

    UNUSED(index);
    scene_manager_handle_custom_event(app->scene_manager, LaEventGpioListDone);
}

void la_scene_gpio_list_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_enter");
    LAApp* app = context;
    submenu_reset(app->gpio_list);

    for(int i = 0; i < app->cfg->port_connections_count; i++) {
        LAPortConnection* connection = &app->cfg->port_connections[i];
        const char* in = la_gpio_items_get_pin_name(app->gpio_items, connection->in);
        const char* out = la_gpio_items_get_pin_name(app->gpio_items, connection->out);

        // Generate label
        char* str = (char*)malloc(20 * sizeof(char));
        str[0] = '\0';
        la_concat(str, in);
        la_concat(str, " -> ");
        la_concat(str, out);

        submenu_add_item(app->gpio_list, str, i, la_gpio_list_menu_callback_edit_con, app);
    }

    // add "Add New" Entry
    submenu_add_item(
        app->gpio_list,
        "+ add new",
        app->cfg->port_connections_count,
        la_gpio_list_menu_callback_create_con,
        app);

    // add "Done" Entry
    submenu_add_item(
        app->gpio_list,
        "Done",
        app->cfg->port_connections_count + 1,
        la_gpio_list_menu_callback_done,
        app);

    view_dispatcher_switch_to_view(app->view_dispatcher, LA_GpioList);
}

void la_scene_gpio_list_on_exit(void* context) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_exit");
    LAApp* app = context;
    app->gpio_list_select_con = submenu_get_selected_item(app->gpio_list);

    submenu_reset(app->gpio_list);
}

bool la_scene_gpio_list_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "la_scene_gpio_list_on_event");
    LAApp* app = context;
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case LaEventGpioListEdit:
            app->gpio_list_select_con = submenu_get_selected_item(app->gpio_list);
            scene_manager_next_scene(app->scene_manager, LaSceneSelectPort);
            return true;
            break;
        case LaEventGpioListCreate:
            // increase counter
            app->cfg->port_connections_count++;
            app->gpio_list_select_con = submenu_get_selected_item(app->gpio_list);
            scene_manager_next_scene(app->scene_manager, LaSceneSelectPort);
            return true;
            break;
        case LaEventGpioListDone:
            if(app->cfg->port_connections_count == 0) {
                // warn that there aren't any port connections
                app->dialog_next_scene = LaSceneGpioList;
                app->dialog_curr_info = "No port\nconnections found!";
                scene_manager_next_scene(app->scene_manager, LaSceneDialog);
            } else if(!valid_port_connections(
                          app->cfg->port_connections, app->cfg->port_connections_count)) {
                // warn that there are duplicate port usages
                app->dialog_next_scene = LaSceneGpioList;
                app->dialog_curr_info = "Duplicate port\nassignment found!";
                scene_manager_next_scene(app->scene_manager, LaSceneDialog);
            } else {
                scene_manager_search_and_switch_to_previous_scene(
                    app->scene_manager, LaSceneCfgScene);
            }
            return true;
            break;
        }
    }
    return false;
}
