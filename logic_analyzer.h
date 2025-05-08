#pragma once
#include "gui/modules/submenu.h"
#include "gui/scene_manager.h"
#include "gui/view_dispatcher.h"

// <-------- App Context -------->
typedef struct {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* gpio_list;
} LAApp;

// <-------- GUI -------->
// View Types
typedef enum {
    LA_Menu
} LAView;
