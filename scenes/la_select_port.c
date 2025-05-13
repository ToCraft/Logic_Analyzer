#include "gui/modules/variable_item_list.h"
#include "gui/scene_manager.h"
#include "la_custom_events.h"
#include <furi.h>
#include "../logic_analyzer.h"
#include "../scenes/la_scene.h"
#include "../util/la_utils.h"

void la_select_port_input(VariableItem* item) {
    LAApp* app = variable_item_get_context(item);
    furi_assert(app);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, la_gpio_items_get_pin_name(app->gpio_items, index));

    // write config
    LAPortConnection* connection = &app->cfg->port_connections[app->gpio_list_select_con];
    connection->in = index;
}

void la_select_port_output(VariableItem* item) {
    LAApp* app = variable_item_get_context(item);
    furi_assert(app);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, la_gpio_items_get_pin_name(app->gpio_items, index));

    // write config
    LAPortConnection* connection = &app->cfg->port_connections[app->gpio_list_select_con];
    connection->out = index;
}

void la_select_port_delete(VariableItem* item) {
    LAApp* app = variable_item_get_context(item);
    furi_assert(app);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, index == 1 ? "True" : "False");

    if(index) {
        // send delete con event
        view_dispatcher_send_custom_event(app->view_dispatcher, LaEventConDelete);
    }
}

void la_scene_select_port_on_enter(void* context) {
    FURI_LOG_T(TAG, "la_scene_select_port_on_enter");
    LAApp* app = context;

    // remove later
    furi_assert(app->gpio_list_select_con < app->cfg->port_connections_count + 1);

    uint16_t gpio_in_index;
    uint16_t gpio_out_index;
    if(app->gpio_list_select_con == app->cfg->port_connections_count) {
        gpio_in_index = 0;
        gpio_out_index = 0;

    } else {
        LAPortConnection* connection = &app->cfg->port_connections[app->gpio_list_select_con];
        gpio_in_index = connection->in;
        gpio_out_index = connection->out;
    }

    variable_item_list_reset(app->select_port);

    // add Input Pin
    VariableItem* in = variable_item_list_add(
        app->select_port,
        "Input",
        la_gpio_items_get_count(app->gpio_items),
        la_select_port_input,
        app);
    variable_item_set_current_value_index(in, gpio_in_index);
    variable_item_set_current_value_text(
        in, la_gpio_items_get_pin_name(app->gpio_items, gpio_in_index));

    // add Output Pin
    VariableItem* out = variable_item_list_add(
        app->select_port,
        "Output",
        la_gpio_items_get_count(app->gpio_items),
        la_select_port_output,
        app);
    variable_item_set_current_value_index(out, gpio_out_index);
    variable_item_set_current_value_text(
        out, la_gpio_items_get_pin_name(app->gpio_items, gpio_out_index));

    // add Delete Option
    VariableItem* del =
        variable_item_list_add(app->select_port, "Delete", 2, la_select_port_delete, app);
    variable_item_set_current_value_index(del, 0);
    variable_item_set_current_value_text(del, "False");

    view_dispatcher_switch_to_view(app->view_dispatcher, LA_SelectPort);
}

void la_scene_select_port_on_exit(void* context) {
    FURI_LOG_T(TAG, "la_scene_select_port_on_exit");
    LAApp* app = context;

    variable_item_list_reset(app->select_port);
}

bool la_scene_select_port_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "la_scene_select_port_on_event");
    LAApp* app = context;
    UNUSED(app);

    if(event.type == SceneManagerEventTypeCustom && event.event == LaEventConDelete) {
        // remove port connection from config
        la_remove_element(
            (void**)app->cfg->port_connections,
            (int*)&app->cfg->port_connections_count,
            app->gpio_list_select_con);
        // head back to the gpio list
        scene_manager_next_scene(app->scene_manager, LaSceneGpioList);
        return true;
    }
    return false;
}
