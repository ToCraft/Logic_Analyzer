#pragma once

#include <furi_hal_gpio.h>

typedef struct LaGPIOItems LaGPIOItems;

LaGPIOItems* la_gpio_items_alloc(void);

void la_gpio_items_free(LaGPIOItems* items);

uint8_t la_gpio_items_get_count(LaGPIOItems* items);

void la_gpio_items_configure_pin(LaGPIOItems* items, uint8_t index, GpioMode mode);

void la_gpio_items_set_pin(LaGPIOItems* items, uint8_t index, bool level);

bool la_gpio_items_get_pin(LaGPIOItems* items, uint8_t index);

const char* la_gpio_items_get_pin_name(LaGPIOItems* items, uint8_t index);
