#ifndef __LOGIC_ANALYZER_H__
#define __LOGIC_ANALYZER_H__

#include "gui/modules/submenu.h"
#include "gui/scene_manager.h"
#include "gui/view_dispatcher.h"
#include <furi.h>

// <-------- Utility Functions -------->
void la_int_to_str(int num, char* str);
void la_concat(char* dest, const char* src);

// <-------- Main Menu Events -------->
void la_scene_on_enter_main_menu(void* context);
bool la_scene_on_event_main_menu(void* context, SceneManagerEvent event);
void la_scene_on_exit_main_menu(void* context);
void la_menu_callback_main_menu(void* context, uint32_t index);

// <-------- App Context -------->
typedef struct {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* menu;
} LAApp;

// <-------- GUI -------->
// View Types
typedef enum {
    LA_Menu
} LAView;
// Scenes
typedef enum {
    LAScene_Main,
    LAScene_PortSelection,
    LASCene_Run,
    LAScene_Eval,
    LAScene_count
} LAScene;
// <-------- Event Callbacks & Handlers -------->
// on_enter, on_event & on_exit handler
void (*const la_scene_on_enter_handlers[])(void*) = {la_scene_on_enter_main_menu};
bool (*const la_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    la_scene_on_event_main_menu};
void (*const la_scene_on_exit_handlers[])(void*) = {la_scene_on_exit_main_menu};
const SceneManagerHandlers la_scene_event_handler = {
    .on_enter_handlers = la_scene_on_enter_handlers,
    .on_event_handlers = la_scene_on_event_handlers,
    .on_exit_handlers = la_scene_on_exit_handlers,
    .scene_num = LAScene_count};
// view dispatcher custom event callback
bool la_scene_manager_custom_event_callback(void* context, uint32_t custom_event);
// view dispatcher navigation event callback
bool la_scene_manager_navigation_event_callback(void* context);

// <-------- Initalization Functions -------->
LAApp* logic_analyzer_init();
void logic_analyzer_scene_manager_init(LAApp* app);
void logic_analyzer_view_dispatcher_init(LAApp* app);
// free memory space
void logic_analyzer_free(LAApp* app);
// <-------- Entry Point -------->
int32_t logic_analyzer_app(void* p);
#endif
