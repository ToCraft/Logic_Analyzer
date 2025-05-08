// based on GPIO scripts
#pragma once
#include <gui/scene_manager.h>

// Generate scene id and total number
#define ADD_SCENE(name, id) LaScene##id,
typedef enum {
#include "la_scene_config.h"
    LaSceneNum,
} LaScene;
#undef ADD_SCENE

extern const SceneManagerHandlers la_scene_handlers;

// Generate scene handlers declaration
#define ADD_SCENE(name, id)                                    \
    void la_scene_##name##_on_enter(void*);                    \
    bool la_scene_##name##_on_event(void*, SceneManagerEvent); \
    void la_scene_##name##_on_exit(void*);
#include "la_scene_config.h"
#undef ADD_SCENE
