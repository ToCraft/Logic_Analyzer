#include "la_gpio_items.h"

#include <furi_hal_resources.h>

struct LaGPIOItems {
    GpioPinRecord* pins;
    size_t count;
};

LaGPIOItems* la_gpio_items_alloc(void) {
    LaGPIOItems* items = malloc(sizeof(LaGPIOItems));

    items->count = 0;
    for(size_t i = 0; i < gpio_pins_count; i++) {
        if(!gpio_pins[i].debug) {
            items->count++;
        }
    }

    items->pins = malloc(sizeof(GpioPinRecord) * items->count);
    size_t index = 0;
    for(size_t i = 0; i < gpio_pins_count; i++) {
        if(!gpio_pins[i].debug) {
            items->pins[index].pin = gpio_pins[i].pin;
            items->pins[index].name = gpio_pins[i].name;
            index++;
        }
    }
    return items;
}

void la_gpio_items_free(LaGPIOItems* items) {
    free(items->pins);
    free(items);
}

uint8_t la_gpio_items_get_count(LaGPIOItems* items) {
    return items->count;
}

void la_gpio_items_configure_pin(LaGPIOItems* items, uint8_t index, GpioMode mode) {
    furi_assert(index < items->count);
    furi_hal_gpio_write(items->pins[index].pin, false);
    furi_hal_gpio_init(items->pins[index].pin, mode, GpioPullNo, GpioSpeedVeryHigh);
}

void la_gpio_items_set_pin(LaGPIOItems* items, uint8_t index, bool level) {
    furi_assert(index < items->count);
    furi_hal_gpio_write(items->pins[index].pin, level);
}

bool la_gpio_items_get_pin(LaGPIOItems* items, uint8_t index) {
    furi_assert(index < items->count);
    return furi_hal_gpio_read(items->pins[index].pin);
}

const char* la_gpio_items_get_pin_name(LaGPIOItems* items, uint8_t index) {
    furi_assert(index < items->count + 1);
    if(index == items->count) {
        return "NONE";
    } else {
        return items->pins[index].name;
    }
}
