#pragma once
#include <stdint.h>
#define TAG "logic_analyzer"

void la_int_to_str(int num, char* str);
void la_concat(char* dest, const char* src);
void la_remove_element(void* arr[], int* size, int index);
uint8_t la_contains(uint8_t* arr, int size, uint8_t* x);
