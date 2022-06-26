//
// Created by Catizard on 2022/6/19.
//

#ifndef SIMPLE_C_STRING_STRING_H
#define SIMPLE_C_STRING_STRING_H

#include <stddef.h>

typedef struct string_s {
    size_t len;
    char *data;
} string_t;

typedef struct string_dict_s {
    size_t _size;
    string_t *dict[];
} string_dict_t;

string_t *string_create(char *);

int string_compare(string_t *, string_t *);

#endif //SIMPLE_C_STRING_STRING_H
