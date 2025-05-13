#include "gui/scene_manager.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_scene_dialog_callback(DialogExResult result, void* context) {
    LAApp* app = context;
    if(result == DialogExResultLeft) {
        scene_manager_search_and_switch_to_previous_scene(app->scene_manager, LaSceneGpioList);
    } else {
        view_dispatcher_switch_to_view(app->view_dispatcher, LaSceneSelectPort);
    }
}

void la_scene_dialog_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_dialog_on_enter");
    LAApp* app = context;

    dialog_ex_reset(app->dialog);

    dialog_ex_set_context(app->dialog, app);
    dialog_ex_set_left_button_text(app->dialog, "Edit");
    dialog_ex_set_right_button_text(app->dialog, "Start");
    dialog_ex_set_header(app->dialog, "Start analyzing?", 22, 12, AlignLeft, AlignTop);
    dialog_ex_set_result_callback(app->dialog, la_scene_dialog_callback);

    view_dispatcher_switch_to_view(app->view_dispatcher, LA_Dialog);
}

void la_scene_dialog_on_exit(void* context) {
    FURI_LOG_T(TAG, "la_scene_dialog_on_exit");
    LAApp* app = context;

    dialog_ex_reset(app->dialog);
}

bool la_scene_dialog_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "la_scene_dialog_on_event");
    LAApp* app = context;
    UNUSED(app);

    UNUSED(event);

    return false;
}
