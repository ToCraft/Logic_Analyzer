#pragma once

#include "furi_hal_resources.h"
#include "util/la_utils.h"

typedef struct {
    uint8_t in;
    uint8_t out;
    uint8_t index;
} LAPortConnection;

typedef struct {
    LAPortConnection* port_connections;
    uint8_t port_connections_count;
} LAConfig;

bool valid_port_connections(LAPortConnection* cons, uint8_t cons_count);
