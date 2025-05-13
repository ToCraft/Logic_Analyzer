#include "gui/scene_manager.h"
#include "la_custom_events.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_scene_dialog_callback(DialogExResult result, void* context) {
    UNUSED(result);
    LAApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, LaEventDialogContinue);
}

void la_scene_dialog_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_dialog_on_enter");
    LAApp* app = context;

    dialog_ex_reset(app->dialog);

    dialog_ex_set_context(app->dialog, app);
    dialog_ex_set_right_button_text(app->dialog, "Continue");
    dialog_ex_set_header(app->dialog, app->dialog_curr_info, 22, 12, AlignLeft, AlignTop);
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

    if(event.type == SceneManagerEventTypeCustom && event.event == LaEventDialogContinue) {
        // switch scene
        view_dispatcher_switch_to_view(app->view_dispatcher, app->dialog_next_scene);
        scene_manager_next_scene(app->scene_manager, LaSceneGpioList);
        return true;
    }
    return false;
}
