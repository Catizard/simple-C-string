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
    /*
     * TODO this is only for test. After completing basic api, dict field will write as a tree structure
     *  in order to save time when searching or modification
     *  dict size is set up as 100, JUST FOR TEST REMEMBER
     */
    string_t **dict;
} string_dict_t;

string_t *string_create(char *);

int string_compare(string_t *, string_t *);

#endif //SIMPLE_C_STRING_STRING_H
