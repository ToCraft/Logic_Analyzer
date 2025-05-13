#include "gui/modules/variable_item_list.h"
#include "gui/scene_manager.h"
#include "la_custom_events.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_cfg_scene_port_map(VariableItem* item) {
    LAApp* app = variable_item_get_context(item);
    furi_assert(app);
    uint8_t index = variable_item_get_current_value_index(item);

    if(index) {
        // send delete con event
        view_dispatcher_send_custom_event(app->view_dispatcher, LaOpenGpioList);
    }
}

void la_scene_cfg_scene_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_cfg_scene_on_enter");
    LAApp* app = context;

    variable_item_list_reset(app->cfg_scene);

    // add Ports menu
    VariableItem* ports =
        variable_item_list_add(app->cfg_scene, "Port Map", 2, la_cfg_scene_port_map, app);
    variable_item_set_current_value_index(ports, 0);
    variable_item_set_current_value_text(ports, "");

    view_dispatcher_switch_to_view(app->view_dispatcher, LA_CfgScene);
}

void la_scene_cfg_scene_on_exit(void* context) {
    FURI_LOG_T(TAG, "la_scene_cfg_scene_on_exit");
    LAApp* app = context;

    variable_item_list_reset(app->cfg_scene);
}

bool la_scene_cfg_scene_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "la_scene_cfg_scene_on_event");
    LAApp* app = context;
    UNUSED(app);

    if(event.type == SceneManagerEventTypeCustom && event.event == LaOpenGpioList) {
        // open gpio list
        scene_manager_next_scene(app->scene_manager, LaSceneGpioList);
        return true;
    }
    return false;
}
