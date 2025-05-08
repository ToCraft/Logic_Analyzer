// based on GPIO scripts
#include "la_scene.h"

// Generate scene on_enter handlers array
#define ADD_SCENE(name, id) la_scene_##name##_on_enter,
void (*const la_scene_on_enter_handlers[])(void*) = {
#include "la_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_event handlers array
#define ADD_SCENE(name, id) la_scene_##name##_on_event,
bool (*const la_scene_on_event_handlers[])(void* context, SceneManagerEvent event) = {
#include "la_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_exit handlers array
#define ADD_SCENE(name, id) la_scene_##name##_on_exit,
void (*const la_scene_on_exit_handlers[])(void* context) = {
#include "la_scene_config.h"
};
#undef ADD_SCENE

// Initialize scene handlers configuration structure
const SceneManagerHandlers la_scene_handlers = {
    .on_enter_handlers = la_scene_on_enter_handlers,
    .on_event_handlers = la_scene_on_event_handlers,
    .on_exit_handlers = la_scene_on_exit_handlers,
    .scene_num = LaSceneNum,
};
