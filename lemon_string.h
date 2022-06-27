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

typedef struct string_slice_s {
    size_t len;
    size_t l, r;
    char *data;
    struct string_slice_s *succ;
    size_t succ_len;
} string_slice_t;

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

int string_compare_fn(string_t *, string_t *, int(*fn)(char *, size_t, char *, size_t));

int string_delete(string_t *);

string_slice_t *string_slice_create(string_t *, size_t, size_t);

int string_slice_delete(string_slice_t *);

string_slice_t *string_slice_merge(string_slice_t *, string_slice_t *);

string_t *slice_to_string(string_slice_t *);

#endif //SIMPLE_C_STRING_STRING_H
