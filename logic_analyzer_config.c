#include "logic_analyzer_config.h"

bool valid_port_connections(LAPortConnection* cons, uint8_t cons_count) {
    FURI_LOG_T(TAG, "valid_port_connections");

    uint8_t used_ports = 0;
    uint8_t* ports = malloc(2 * cons_count * sizeof(uint8_t));

    if(!ports) {
        // couldn't allocate "ports"
        return false;
    }

    for(uint8_t i = 0; i < cons_count; i++) {
        if(la_contains(ports, used_ports, &cons[i].in)) {
            free(ports);
            return false;
        } else {
            ports[used_ports] = cons[i].in;
            used_ports++;
        }
        if(la_contains(ports, used_ports, &cons[i].out)) {
            free(ports);
            return false;
        } else {
            ports[used_ports] = cons[i].out;
            used_ports++;
        }
    }

    free(ports);
    return true;
}
