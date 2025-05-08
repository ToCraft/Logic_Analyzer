#pragma once
#include "gui/scene_manager.h"
#include "gui/view_dispatcher.h"
#include "gui/modules/submenu.h"
#include "gui/modules/variable_item_list.h"
#include "la_gpio_items.h"
#include "logic_analyzer_config.h"

// <-------- App Context -------->
typedef struct {
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    LaGPIOItems* gpio_items;
    LAConfig* cfg;

    Submenu* gpio_list;
    uint16_t gpio_list_select_con;

    VariableItemList* select_port;
} LAApp;

// <-------- GUI -------->
// View Types
typedef enum {
    LA_GpioList,
    LA_SelectPort
} LAView;
