#include "la_utils.h"

void la_int_to_str(int num, char* str) {
    int i = 0;
    if(num == 0) {
        str[i++] = '0';
    } else {
        while(num > 0) {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
    }
    str[i] = '\0';
    for(int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void la_concat(char* dest, const char* src) {
    while(*dest) {
        dest++;
    }
    while(*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void la_remove_element(void* arr[], int* size, int index) {
    if(index < 0 || index >= *size) {
        // Invalid index
        return;
    }
    // Shift pointers to the left
    for(int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    // reduce size
    (*size)--;
}

// 0 - False, 1 - True
uint8_t la_contains(uint8_t* arr, int size, uint8_t* x) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == *x) {
            return 1;
        }
    }
    return 0;
}
