#include <string.h>
#include <malloc.h>
#include "lemon_string.h"

string_dict_t DICT;

int _string_compare_raw(string_t *LHS, const char *RHS) {
    size_t size_rhs = strlen(RHS);
    if (size_rhs != LHS->len) {
        return 0;
    }

    for (int i = 0; i < LHS->len; i++) {
        if (LHS->data[i] != RHS[i]) {
            return 0;
        }
    }
    return 1;
}

string_t *_search_string_in_dict(const char *rawstring) {
    //TODO change dict's structure in order to get faster search prog
    for (int i = 0; i < DICT._size; i++) {
        if (_string_compare_raw(DICT.dict[i], rawstring)) {
            return DICT.dict[i];
        }
    }
    return NULL;
}

string_t *string_create(char *rawstring) {
    string_t *fs = _search_string_in_dict(rawstring);
    if (fs != NULL) {
        return fs;
    }
    string_t *new_s = (string_t *) malloc(sizeof(string_t));
    new_s->len = strlen(rawstring);
    char *alloc_string = (char *) malloc(new_s->len);
    memcpy(alloc_string, rawstring, new_s->len);
    new_s->data = alloc_string;
    return new_s;
}

int string_compare(string_t *LHS, string_t *RHS) {
    return _string_compare_raw(LHS, RHS->data);
}

int string_delete(string_t *str) {
    free(str->data);
    free(str);
    return 1;
}
